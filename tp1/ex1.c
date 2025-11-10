#include <stdio.h>
#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <threads.h>

void *fun(void *arg);

int main(void) {
    printf("Hello, World!\n");
    pthread_t t;

    int arg = 2;
    int err = pthread_create(&t, NULL, (void *) fun, &arg);
    if (err) {
        perror("error creating thread");
        exit(EXIT_FAILURE);
    }
    pthread_join(t, NULL);
    return 0;
}

void *fun(void *arg) {
    int state = 0;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_getdetachstate(&attr, &state);
    if (state == PTHREAD_CREATE_DETACHED) {
        printf("Thread is detached\n");
    }
    else {
        printf("Thread is joinable\n");
    }
    pthread_attr_getscope(&attr, &state);
    if (state == PTHREAD_SCOPE_PROCESS) {
        printf("Thread is process scope\n");
    }
    else {
        printf("Thread is system scope\n");
    }
    return NULL;
}
