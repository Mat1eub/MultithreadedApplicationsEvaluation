#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "../headers/philosopher.h"
#include "../headers/producerconsummer.h"

#define BUFFER_SIZE 8 // Prod/Cons problem

// Philo's problem
int N;
sem_t* forks;

// Prod/cons problem
int P;
int C;
pthread_mutex_t mutex_prodcons;
sem_t cvides;
sem_t cremplies;


int main(int argc, char* argv[]) {
    
    /*************************/
    /* Philosophers' problem */
    /*************************/
    if (strcmp(argv[0],"./philosophers_exec")==0){
        if (argc != 2) {
            fprintf(stderr, "Usage: %s N=<number_of_philosophers>\n", argv[0]);
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
    }
    /**********************************/
    /* Producer - Consummer's problem */
    /**********************************/
    if(strcmp(argv[0],"./producerconsummer_exec")==0){
        if (argc != 3) {
            fprintf(stderr, "Usage: %s P=<number_of_producers> C=<number_of_consummers>\n", argv[0]);
            return 1;
        }

        // Get A&B from commande line
        P = atoi(argv[1]);
        if (P <= 0) {
            fprintf(stderr, "Invalid number of producers.\n");
            return 1;
        }

        C = atoi(argv[2]);
        if (C <= 0) {
            fprintf(stderr, "Invalid number of consummers.\n");
            return 1;
        }
        
        // Initialization
        pthread_t producers[P];     // Threads for each producers
        pthread_t consummers[C];    // Threads for each consummers
        
        pthread_mutex_init(&mutex_prodcons, NULL);
        sem_init(&cvides,0,BUFFER_SIZE);
        sem_init(&cremplies,0,0);

        // Starting threads' work
        for (size_t i = 0; i < P; i++)
        {
            pthread_create(&producers[i], NULL,producer,(void*)producers[i]);
        }

        for (size_t i = 0; i < C; i++)
        {
            pthread_create(&consummers[i], NULL,consummer,NULL);
        }
        
        // Threads' results
        for (int i = 0; i < P; i++) {
            pthread_join(producers[i], NULL);
        }
        for (int i = 0; i < C; i++) {
            pthread_join(consummers[i], NULL);
        }
        
        pthread_mutex_destroy(&mutex_prodcons);
        sem_destroy(&cvides);
        sem_destroy(&cremplies);
    }
    return 0;
}