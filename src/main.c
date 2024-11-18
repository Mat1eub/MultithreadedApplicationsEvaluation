#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include "../headers/philosopher.h"

int N;
sem_t* forks;

int main(int argc, char* argv[]) {
    
    /* Philosophers' problem */

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_philosophers>\n", argv[0]);
        return 1;
    }

    // Get N from commande line
    N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Invalid number of philosophers.\n");
        return 1;
    }

    // Allocate dynamically the semaphore array of forks
    forks = malloc(N*sizeof(sem_t));

    if (!forks) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Threads for each philosopher
    pthread_t philosophers[N];       
    int indices[N];                  

    // Each philosopher in a thread 
    for (int i = 0; i < N; i++) {
        indices[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &indices[i]);
    }

    // Threads' results
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    free(forks);

    /* Producer/Consummer problem */

    return 0;
}