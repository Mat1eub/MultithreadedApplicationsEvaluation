#include <pthread.h>
#include <semaphore.h>
#include "../headers/readerswriters.h"

/* Initialization */
sem_t* access;
int readerscount;
pthread_mutex_t mutex;

int wcount = 0;
int rcount = 0;

#define MAX_WRITES 640
#define MAX_READES 2540

void process(){
    for (int i=0; i<10000; i++);
}

void* writer(void* arg){
    while(1){
        // Vérifie nombre d'écritures
        pthread_mutex_lock(&mutex);
        if (wcount >= MAX_WRITES) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        wcount++;
        pthread_mutex_unlock(&mutex);

        sem_wait(&access);

        // Critical section : 1 writer 0 reader
        process();

        sem_post(&access);
    }
    return NULL;
}

void* reader(void* arg){
    while(1){
        pthread_mutex_lock(&mutex); // Reader comes -> modify readerscount
        if(rcount >= MAX_READES){
            pthread_mutex_unlock(&mutex);
            break;
        }
        rcount++;
        readerscount++;
        if(readerscount==1){ // If it's the first reader, we shut down access to writers
            sem_wait(&access);
        }
        pthread_mutex_unlock(&mutex);

        process(); // Read

        pthread_mutex_lock(&mutex); // Reader leaves -> modify readerscount
        readerscount--;
        if(readerscount==0){ // If it's the last reader, we free the semaphore for the writers
            sem_post(&access);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
