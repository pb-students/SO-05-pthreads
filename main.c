#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int counter = 0;

void* increment (void* arg) {
    while (1) {
        ++counter;
        sleep(1);
    }
}

void* print (void* arg) {
    while (1) {
        printf("counter = %d\n", counter);
        sleep(1);
    }
}

int main() {
    pthread_t threads[2];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    int error = 1;
    do {
        if (pthread_create(&threads[0], &attr, increment, NULL)) break;
        if (pthread_create(&threads[1], &attr, print, NULL)) break;
        error = 0;
    } while (0);

    pthread_attr_destroy(&attr);

    if (error) {
        fprintf(stderr, "Error creating new thread.");
        exit(EXIT_FAILURE);
    }

    void *status;
    error = 1;
    do {
        if (pthread_join(threads[0], &status)) break;
        if (pthread_join(threads[1], &status)) break;
        error = 0;
    } while (0);

    if (error) {
        fprintf(stderr, "Error joining threads.");
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}
