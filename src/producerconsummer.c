#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/producerconsummer.h"

// Detailed explaination in the README's Producters-Consummers section

// Initial variables
#define N 8
#define NB_ITEMS 131072
int buff[N];
int* buffer = buff;

int prodcount = 0;      // Keeps track of the number of producer
int consumcount = 0;    // Keeps track of the number of consummer

void process (){
    for (int i=0; i<10000; i++);
}

void* producer(void* arg){
    int* id = (int*)arg;
    static int ip = 0;   // Indicates where we are in the buffer
    while(1){
        sem_wait(&cvides);
        pthread_mutex_lock(&mutex_prodcons);

        if (prodcount>=NB_ITEMS)
        {
            pthread_mutex_unlock(&mutex_prodcons);
            break;
        }
        
        // Critical section
        prodcount++; 
        buffer[ip] = *id;
        ip = (ip+1)%N;
        // Debugging : printf("Producer %d: prodcount=%d, ip=%d\n", *id, prodcount, ip);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cremplies);

    }
    return NULL;
}

void* consummer(void* arg){
    static int ic = 0;
    while(1){
        sem_wait(&cremplies);
        pthread_mutex_lock(&mutex_prodcons);
        if (consumcount>=NB_ITEMS && prodcount >= NB_ITEMS) // If nb of producted and consummed items>NB_ITEMS we stop
        {
            pthread_mutex_unlock(&mutex_prodcons);
            break;
        }
        
        // Critical section
        consumcount++;
        int element = buffer[ic];
        ic = (ic+1)%N;
        // Debugging : printf("Consumer: consumcount=%d, element=%d\n", consumcount, element);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cvides);
        
    }
    return NULL;
}