#include <semaphore.h>
#include <stdio.h>

/* Initialisation des variables */
#define N 5              // Nombre de philosophes à entrer par ligne de commande
#define COUNT 10e6       // Nombre de cycles penser/manger
sem_t forks[N];          // Une sémaphore pour chaque fourchette

void* philosopher(void* j) {
    int i = *(int*)j;             
    int right = i;                   
    int left = (i + 1) % N;          

    for (size_t j = 0; j < COUNT; j++) {
        if (i == N - 1) {            // Dernier philosophe prend les fourchettes dans un ordre inversé pour éviter un deadlock
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        } else {
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        }

        // Philosophe mange (section critique)
        // Ici, on ne fait rien car manger est instantané.

        sem_post(&forks[left]);    // Le philosophe libère les fourchettes
        sem_post(&forks[right]);
    }

    return NULL;
}