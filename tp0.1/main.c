#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    time_t t = time(NULL);
    printf("Today is %s, with UUID %u\n", ctime(&t), getuid());//standard output debug

    pid_t pid = fork();

    if (pid == 0) {//child 1
        printf("Child 1 (aborted), my pid is %d\n", getpid());
        exit(3);
    } else { //parent
        pid = fork();
        if (pid == 0) { //child 2
            printf("Child 2, my pid is %d\n", getpid());
            int *p = NULL;
            *p = 42; //segmentation fault
        } else {
            //parent
            pid = fork();
            if (pid == 0) {
                //child 3
                printf("Child 3, my pid is %d\n", getpid());
                int i = 5;
                int a = 20 / (i - 5); //division by zero
            } else { // parent
                int status = 0;
                for (uint8_t i = 0; i < 3; i++) {
                    short cpid = wait(&status);
                    if (WIFEXITED(status))
                        printf("Child %d terminated with status %d, all correct\n", cpid, status);
                    else
                        if (WIFSIGNALED(status)) {
                            int numSignal = WTERMSIG(status);
                            printf("Fin anormale, numSignal = %d qui correspond à %s\n", numSignal, strsignal(numSignal));
                        }
                }
            }
        }
    }
    return 0;
}