#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../include/fctsemaphore_TS.h"

int N;
Semaphore* forks;
#define COUNT 1000000  // Nombre de cycles penser/manger

// Fonction pour vérifier les erreurs lors de la création des threads
void* philosopher(void* param) {
    int i = *(int*)param;
    int right = i;
    int left = (i + 1) % N;

    for (size_t j = 0; j < COUNT; j++) {
        // Philosophe pense (no-op)

        // Dernier philosophe prend les fourchettes dans un ordre inversé pour éviter un deadlock
        if (i == N - 1) {
            locksem(&forks[right]);
            locksem(&forks[left]);
        } else {
            locksem(&forks[left]);
            locksem(&forks[right]);
        }

        // Philosophe mange (no-op)

        unlocksem(&forks[left]);  // Libère les fourchettes
        unlocksem(&forks[right]);
    }

    return NULL;
}

int main(int argc, char const *argv[]) {
    // Vérification des arguments de la commande
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N=<number_of_philosophers>\n", argv[0]);
        return 1;
    }

    // Récupérer le nombre de philosophes (N)
    N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "Invalid number of philosophers.\n");
        return 1;
    }

    // Allocation dynamique du tableau de sémaphores pour les fourchettes
    forks = malloc(N * sizeof(Semaphore));
    if (forks == NULL) {
        fprintf(stderr, "Failed to allocate memory for forks\n");
        exit(EXIT_FAILURE);
    }
    // Initialisation des sémaphores
    for (int i = 0; i < N; i++) {
        initsem(&forks[i], 1);  // Initialisation des fourchettes disponibles (1)
    }

    // Création des threads pour chaque philosophe
    pthread_t philosophers[N];
    int indices[N];

    for (int i = 0; i < N; i++) {
        indices[i] = i;
        int result = pthread_create(&philosophers[i], NULL, philosopher, &indices[i]);
        if (result != 0) {
            fprintf(stderr, "Error creating thread %d: %s\n", i, strerror(result));
            return 1;
        }
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < N; i++) {
        int result = pthread_join(philosophers[i], NULL);
        if (result != 0) {
            fprintf(stderr, "Error joining thread %d: %s\n", i, strerror(result));
            return 1;
        }
    }

    // Libération de la mémoire allouée pour les sémaphores
    free(forks);

    return 0;
}
