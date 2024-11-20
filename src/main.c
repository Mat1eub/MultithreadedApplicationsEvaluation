#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "../headers/philosopher.h"
#include "../headers/producerconsummer.h"

#define BUFFER_SIZE 8

// Philo's problem
int N;
sem_t* forks;

// Prod/cons problem
int A;
int B;
pthread_mutex_t mutex_prodcons;
sem_t cvides;
sem_t cremplies;


int main(int argc, char* argv[]) {
    
    /*********************** */
    /* Philosophers' problem */
    /*********************** */
    if (strcmp(argv[0],"./philosophers_exec")==0){
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
    }
    /**********************************/
    /* Producer - Consummer's problem */
    /**********************************/
    if(strcmp(argv[0],"./producerconsummer_exec")==0){
        if (argc != 3) {
            fprintf(stderr, "Usage: %s <number_of_producers> <number_of_consummers>\n", argv[0]);
            return 1;
        }

        // Get A&B from commande line
        A = atoi(argv[1]);
        if (A <= 0) {
            fprintf(stderr, "Invalid number of producers.\n");
            return 1;
        }

        B = atoi(argv[2]);
        if (B <= 0) {
            fprintf(stderr, "Invalid number of consummers.\n");
            return 1;
        }
        
        // Initialization
        //int indices_prod[A];
        pthread_t producers[A];

        //int indices_cons[B];
        pthread_t consummers[B];
        
        pthread_mutex_init(&mutex_prodcons, NULL);
        sem_init(&cvides,0,BUFFER_SIZE); // 8 number of slots in the buffer
        sem_init(&cremplies,0,0);

        for (size_t i = 0; i < A; i++)
        {
            pthread_create(&producers[i], NULL,producer,(void*)producers);
        }

        for (size_t i = 0; i < B; i++)
        {
            pthread_create(&consummers[i], NULL,consummer,NULL);
        }
        
        // Threads' results
        for (int i = 0; i < A; i++) {
            pthread_join(producers[i], NULL);
        }
        for (int i = 0; i < B; i++) {
            pthread_join(consummers[i], NULL);
        }
        
        pthread_mutex_destroy(&mutex_prodcons);
        sem_destroy(&cvides);
        sem_destroy(&cremplies);
    }
    return 0;
}