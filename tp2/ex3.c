//
// Created by maxence on 9/15/25.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREADS 5

#define MANGER 0
#define PENSER 1

struct Thread {
    int id;
    int manger;
    int etat;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int fourchettes[THREADS];


void* fun_threads(void *arg) {
    struct Thread self;
    self.id = *(int*)arg;
    self.manger = 0;


    if (self.etat == MANGER) {
        pthread_mutex_lock(&mutex);
        if (fourchettes[self.id] == 0 && fourchettes[self.id + 1] == 0) {
            self.manger += 1;
            fourchettes[self.id] = 1;
            fourchettes[self.id + 1] = 1;
        }
        pthread_mutex_unlock(&mutex);
    }
    printf("Je suis le thread %d\n",self.id);
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t threads[THREADS];
    return 0;
}