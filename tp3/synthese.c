//
// Created by maxence on 11/10/25.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 10

struct {
    long first;
    long last;
} typedef indices;

int *t = NULL;

void *sortArray(void *p) {
    const indices *tp_p = (indices *)p;
    const long first = tp_p->first;
    const long last = tp_p->last;

    free(p);
    printf("first : %lu, last : %lu\n", first, last);

    for (long i = first; i < last - 1; i++) {
        for (long j = first; j < last - (i - first) - 1; j++) {
            if (t[j] > t[j + 1]) {
                const int tmp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = tmp;
            }
        }
    }
    return NULL;
}

int create_array(int **tableau, const long size) {
    *tableau = (int *) calloc(size,sizeof(int));
    for (int i = 0; i < size; i++) {
        (*tableau)[i] = rand() % 100000;
    }
    return 0;
}

void merge(int *arr, long start, long mid, long end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    printf("start : %lu, mid : %lu, last : %lu\n", start, mid, end);

    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));

    memcpy(L, arr + start, n1 * sizeof(int));
    memcpy(R, arr + mid + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}



int main(const int argc, char **argv) {
    long size;
    if (argc < 2) {
        size = 10000;
    } else {
        size = strtol(argv[1],NULL,10);
    }
    printf("Starting program with size of %lu\n",size);
    pthread_t threads[N];
    printf("Creating array\n");
    create_array(&t, size);

    for (long i = 0; i < size; i++) {
        printf("%d ", t[i]);
    }
    printf("\n\n");

    printf("Starting threads\n");
    for (int i = 0; i < N; i++) {
        indices *in = calloc(1, sizeof(indices));
        in->first = i * size / N;
        in->last = (i + 1) * size / N;
        pthread_create(&threads[i], NULL, sortArray, in);
    }

    printf("Joining threads\n");
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Done\n");

    printf("Array :\n");
    for (long i = 0; i < size; i++) {
        if (i % (size / N) == 0)
            printf("\n");
        printf("%d ", t[i]);
    }
    printf("\n\n");

    printf("Merging array\n");

    long chunk = size / N; // size of each sorted segment

    // Make a copy of N (number of segments) that shrinks each merge pass
    int num_segments = N;

    // Temporary variables for merge loop
    while (num_segments > 1) {
        int merged = 0;
        for (int i = 0; i < num_segments - 1; i += 2) {
            long start = i * chunk;
            long mid   = (i + 1) * chunk - 1;
            long end   = ((i + 2) * chunk) - 1;
            if (end >= size) end = size - 1;

            merge(t, start, mid, end);
            merged++;
        }

        // If we had an odd segment left, move it up to next level
        if (num_segments % 2 != 0) {
            // The last segment is already in place, just count it
            merged++;
        }

        // After merging pairs, update chunk size and number of segments
        chunk *= 2;
        num_segments = merged;
    }

    printf("Array :\n");
    for (long i = 0; i < size; i++) {
        printf("%d ", t[i]);
    }
    printf("\n\n");

    printf("Freeing memory and finishing program gracefully\n");

    free(t);
    return 0;
}