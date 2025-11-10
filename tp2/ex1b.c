#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

int cpt = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_fun(void *) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 10000; i++) {
        cpt += 1;
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(void) {
    pthread_t thread[5];

    for (int i = 0; i < 5; i++) {
        const int err = pthread_create(&thread[i], NULL, thread_fun, NULL);
        if (err != 0) {
            printf("Error creating thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 5; i++) {
        const int err = pthread_join(thread[i], NULL);
        if (err != 0) {
            printf("Error joining thread %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    printf("%d\n",cpt);
    exit(EXIT_SUCCESS);
}
