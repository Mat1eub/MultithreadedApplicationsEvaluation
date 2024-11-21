#include <semaphore.h>
#include <stdio.h>
#include "../headers/philosophers.h"

#define COUNT 10e6       // Nombre de cycles penser/manger
// For the philosphers N= nbr of philosphes but also nb of threads ?
void* philosopher(void* param) {
    int i = *(int*)param;             
    int right = i;                   
    int left = (i + 1) % N;          

    for (size_t j = 0; j < COUNT; j++) {

        // Philosophe pense
        // On ne fait rien car penser est instantané

        if (i == N - 1) {            // Dernier philosophe prend les fourchettes dans un ordre inversé pour éviter un deadlock
            sem_wait(&forks[right]);
            sem_wait(&forks[left]);
        } else {
            sem_wait(&forks[left]);
            sem_wait(&forks[right]);
        }

        // Philosophe mange (section critique)
        // Ici aussi, on ne fait rien car manger est instantané.

        sem_post(&forks[left]);    // Le philosophe libère les fourchettes
        sem_post(&forks[right]);
    }

    return NULL;
}