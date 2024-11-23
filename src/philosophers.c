#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int N;
sem_t* forks;
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

int main(int argc, char const *argv[])
{
    char const* problem = argv[0];
    
    if (strcmp(problem,"./philosophers_exec")==0 || strcmp(problem,"./philo")==0){
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
    }
    return 0;
}
