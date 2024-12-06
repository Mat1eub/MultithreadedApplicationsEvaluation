#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fctsemaphore_TS.c"

#define BUFFER_SIZE 8
#define NB_ITEMS 131072

int buff[BUFFER_SIZE];
int* buffer = buff;

int prodcount = 0;      // Keeps track of the number of producer
int consumcount = 0;    // Keeps track of the number of consummer

int P;
int C;

int mutex_prodcons = 0; // Spinlock for critical sections
Semaphore cvides;       // Semaphore for empty slots
Semaphore cremplies;    // Semaphore for filled slots

void process() {
    for (int i = 0; i < 10000; i++);
}

void* producer(void* arg) {
    int* id = (int*)arg;
    static int ip = 0;   // Indicates where we are in the buffer
    while (1) {
        locksem(&cvides);
        lock(&mutex_prodcons);

        if (prodcount >= NB_ITEMS) {
            unlock(&mutex_prodcons);
            unlocksem(&cremplies);
            break;
        }

        // Critical section
        prodcount++;
        buffer[ip] = *id;
        ip = (ip + 1) % BUFFER_SIZE;
        printf("Producer %d: prodcount=%d, ip=%d\n", *id, prodcount, ip);

        unlock(&mutex_prodcons);
        process();
        unlocksem(&cremplies);
    }
    return NULL;
}

void* consummer(void* arg) {
    static int ic = 0;
    while (1) {
        locksem(&cremplies);
        lock(&mutex_prodcons);

        if (consumcount >= NB_ITEMS) {
            unlock(&mutex_prodcons);
            unlocksem(&cvides);
            break;
        }

        // Critical section
        consumcount++;
        int element = buffer[ic];
        ic = (ic + 1) % BUFFER_SIZE;
        printf("Consumer: consumcount=%d, element=%d\n", consumcount, element);

        unlock(&mutex_prodcons);
        process();
        unlocksem(&cvides);
    }
    return NULL;
}

int main(int argc, char const *argv[]) { 
    const char* executable = argv[0];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s P=<number_of_producers> C=<number_of_consummers>\n", argv[0]);
    }

    P = atoi(argv[1]);
    C = atoi(argv[2]);

    if (strcmp(executable, "./prodcons") == 0) {
        if (argc != 2) {
            fprintf(stderr, "Usage: %s <total_number_of_threads>\n", argv[0]);
            return 1;
        }

        int totalThreads = atoi(argv[1]);
        if (totalThreads <= 0) {
            fprintf(stderr, "Invalid total number of threads: %d\n", totalThreads);
            return 1;
        }

        if (totalThreads % 2 == 0) {
            P = totalThreads / 2;
            C = totalThreads / 2;
        } else {
            P = (totalThreads + 1) / 2;
            C = totalThreads / 2;
        }
    }

    if (P <= 0) {
        fprintf(stderr, "Invalid number of producers.\n");
        return 1;
    }

    if (C <= 0) {
        fprintf(stderr, "Invalid number of consummers.\n");
        return 1;
    }

    pthread_t producers[P];
    int thread_id[P];
    pthread_t consummers[C];

    initsem(&cvides, BUFFER_SIZE);
    initsem(&cremplies, 0);

    for (size_t i = 0; i < P; i++) {
        thread_id[i] = i;
        pthread_create(&producers[i], NULL, producer, (void*)(&(thread_id[i])));
    }

    for (size_t i = 0; i < C; i++) {
        pthread_create(&consummers[i], NULL, consummer, NULL);
    }

    for (int i = 0; i < P; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < C; i++) {
        pthread_join(consummers[i], NULL);
    }

    return 0;
}
