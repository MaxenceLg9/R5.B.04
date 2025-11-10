//
// Created by maxence on 9/8/25.
//
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void * fun_thread1(void *arg) {
    const int n = *((int *) arg);
    printf("First thread %lu, Received from main thread : %d\n", pthread_self(), n);
    return NULL;
}

void * fun_thread2(void *arg) {
    printf("Second thread %lu, Received from main thread : %s\n", pthread_self(), (char *) arg);
    char *returned = (char *) malloc(strlen(arg) + 1);
    char *s = arg;
    int i = 0;
    while (*(s + i)) {
        returned[i] = toupper((unsigned char) *(s + i));
        i++;
    }
    returned[i] = '\0';
    return returned;
}

int main(int argc, char **argv) {
    pthread_t thread[2];
    int nombre = 2;
    char msg[] = "Max verstappine";
    int err = pthread_create(&thread[0], NULL, fun_thread1, &nombre);
    if (err) {
        perror("eror creating thread");
    }
    err = pthread_create(&thread[1], NULL, fun_thread2, msg);
    if (err) {
        perror("eror creating thread");
    }
    pthread_join(thread[0], NULL);
    printf("Got from thread 1 %lu\n", thread[0]);
    char *returned = NULL;
    pthread_join(thread[1], (void *) &returned);
    printf("Got from thread 2 %lu : %s\n", thread[1], returned);
    free(returned);
}