#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include "../headers/philosophers.h"
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
    
    const char* problem = argv[0];

    /*************************/
    /* Philosophers' problem */
    /*************************/
    if (strcmp(problem,"./philosophers_exec")==0 || strcmp(problem,"./philo_graphs")==0){
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
    } // End of philo's problem

    /**********************************/
    /* Producer - Consummer's problem */
    /**********************************/
    if(strcmp(problem,"./producerconsummer_exec")==0 || strcmp(problem,"./prodcons_graphs")==0){

        // Get P&C from commande line
        if(argc == 2){
            // Single argument : we split the threads
            int totalThreads = atoi(argv[1]);
            if (totalThreads <= 0) {
                fprintf(stderr, "Invalid total number of threads: %d\n", totalThreads);
                return 1;
            }
            if(totalThreads%2==0){
                P = totalThreads/2;
                C = totalThreads/2;
            }else{
                P = (totalThreads+1)/2;
                C = (totalThreads)/2;
            }
        }else if(argc ==3){
            P = atoi(argv[1]);
            if (P <= 0) {
                fprintf(stderr, "Invalid number of producers.\n");
                return 1;
            }

            C = atoi(argv[2]);
            if (C <= 0) {
                fprintf(stderr, "Invalid number of consummers.\n");
                return 1;
            }else{
            fprintf(stderr, "Usage: %s P=<number_of_producers> C=<number_of_consummers>\n Or:\n %s <total_number_to_dispatch>\n",argv[0], argv[0]);
            return 1;
            }
        }

        // Initialization
        pthread_t producers[P];     // Threads for each producers
        int thread_id[P];
        pthread_t consummers[C];    // Threads for each consummers

        pthread_mutex_init(&mutex_prodcons, NULL);
        sem_init(&cvides,0,BUFFER_SIZE);
        sem_init(&cremplies,0,0);

        // Starting threads' work
        for (size_t i = 0; i < P; i++)
        {
            thread_id[i]=i;
            pthread_create(&producers[i], NULL,producer,(void*)(&(thread_id[i])));
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
    } // End of prodcons' problem

    /******************************/
    /* Readers - writers' problem */
    /******************************/

    
    return 0;
}