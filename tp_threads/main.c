#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/unistd.h>

void* fun_thread(void *arg) {
    printf("From thread : %lu, Pid : %d\n",pthread_self(),getpid());
    return NULL;
}

int main(void) {
    pthread_t thread;
    int err = pthread_create(&thread, NULL, fun_thread, NULL);
    if (err != 0) {
        perror("error creating thread");
        exit(EXIT_FAILURE);
    }
    printf("From thread %lu, Pid : %d\n",pthread_self(),getpid());
    err = pthread_join(thread, NULL);
    if (err != 0) {
        perror("error creating thread");
        exit(EXIT_FAILURE);
    }
    return 0;
}
