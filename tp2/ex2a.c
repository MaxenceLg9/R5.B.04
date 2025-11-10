#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define THREAD_NUMBERS 4

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool start = true;


void* thread_fun(void *arg) {
    long index = (long) arg;
    char message[50];
    while (start == true) {}
    snprintf(message,50,"From : %d, Je suis le thread %lu",index, pthread_self());
    for (int i = 0; i < strlen(message); i++) {
        printf("%c",message[i]);
        fflush(stdout);
        usleep(2000);
    }
    return NULL;
}

int main(void) {
    pthread_t thread[THREAD_NUMBERS];

    for (long i = 0; i < THREAD_NUMBERS; i++) {
        const int err = pthread_create(&thread[i], NULL, thread_fun, (void *) i);
        if (err != 0) {
            printf("Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    start = false;

    for (int i = 0; i < THREAD_NUMBERS; i++) {
        const int err = pthread_join(thread[i], NULL);
        if (err != 0) {
            printf("Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}