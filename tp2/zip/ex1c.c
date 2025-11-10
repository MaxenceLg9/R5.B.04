#include <math.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool start;

void* thread_fun(void *arg) {
    int *cpt = (int*)arg;
    for (int i = 0; i < 100; i++) {
        pthread_mutex_lock(&mutex);
        for (int x = 0; x < 100; x++) {
            *cpt += 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(void) {
    pthread_t thread[5];
    int cpt = 0;

    for (int i = 0; i < 5; i++) {
        const int err = pthread_create(&thread[i], NULL, thread_fun, &cpt);
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
