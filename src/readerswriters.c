#include <pthread.h>
#include <semaphore.h>
#include "../headers/readerswriters.h"

/* Initialization */
sem_t* access;
int readcount;
pthread_mutex_t mutex;


void* writer(void* arg){
    while(1){
        sem_wait(&access);

        // Critical section : 1 writer 0 reader
        for (int i=0; i<10000; i++);

        sem_post(&access);
    }
    return NULL;
}

void* reader(void* arg){
    while(1){
        pthread_mutex_lock(&mutex); // Reader comes -> modify readcount 
            readcount++;
            if(readcount==1){ // If it's the first reader, we shut down access to writers
                sem_wait(&access);
            }
        pthread_mutex_unlock(&mutex);

        // Read (critical sections for readers)
        for (int i=0; i<10000; i++);

        pthread_mutex_lock(&mutex); // Reader leaves -> modify readcount
            readcount--;
            if(readcount==0){ // If it's the last reader, we free the semaphore for the writers
                sem_post(&access);
            }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
