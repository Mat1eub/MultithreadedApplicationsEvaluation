#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fctsemaphore_TTS.h"

int N;
Semaphore* forks;
#define COUNT 1e6       // Nombre de cycles penser/manger

void* philosopher(void* param) {
    int i = *(int*)param;             
    int right = i;                   
    int left = (i + 1) % N;          

    for (size_t j = 0; j < COUNT; j++) {

        // Philosophe pense
        // On ne fait rien car penser est instantané

        if (i == N - 1) {            // Dernier philosophe prend les fourchettes dans un ordre inversé pour éviter un deadlock
            locksem(&forks[right]);
            locksem(&forks[left]);
        } else {
            locksem(&forks[left]);
            locksem(&forks[right]);
        }

        // Philosophe mange (section critique)
        // Ici aussi, on ne fait rien car manger est instantané.

        unlocksem(&forks[left]);    // Le philosophe libère les fourchettes
        unlocksem(&forks[right]);
    }

    return NULL;
}

int main(int argc, char const *argv[])
{
    char const* problem = argv[0];
    
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N=<number_of_philosophers>\n", argv[0]);
        return 1;
    }

    // Get N from commande line (N = nbr of philosophers = nbr of threads too)
    N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Invalid number of philosophers.\n");
        return 1;
    }

    // Allocate dynamically the semaphore array of forks
    forks = malloc(N*sizeof(Semaphore));

    if (!forks) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        initsem(&forks[i], 1);
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

    free(forks);

    return 0;
}

