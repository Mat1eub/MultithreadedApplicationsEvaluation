#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int main() {
    pthread_t philosophers[N];       // Threads pour les philosophes
    int indices[N];                  // Indices pour chaque philosophe

    // Initialisation des sémaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Création des threads
    for (int i = 0; i < N; i++) {
        indices[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &indices[i]);
    }

    // Attente de la fin des threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destruction des sémaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}