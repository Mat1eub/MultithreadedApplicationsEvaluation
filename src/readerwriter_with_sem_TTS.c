#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../include/fctsemaphore_TTS.h"

int rmutex = 0;  
int wmutex = 0;  
int z = 0;
int tot = 0;    

Semaphore rsem;  
Semaphore wsem;  

int rcount = 0; 
int wcount = 0; 

int nb_read = 2540;  
int nb_write = 640;  

void data() {
    for (int i = 0; i < 10000; i++);
}

void* reader() {
    while (1) {
        lock(&tot);
        if (nb_read <= 0) {
            unlock(&tot);
            break;
        }
        nb_read--;  
        unlock(&tot);

        lock(&z);
        locksem(&rsem); 
        lock(&rmutex);
        rcount++;
        if (rcount == 1) locksem(&wsem);
        unlock(&rmutex);
        unlocksem(&rsem);
        unlock(&z);

        data();  

        lock(&rmutex);
        rcount--;
        if (rcount == 0) unlocksem(&wsem);
        unlock(&rmutex);
    }
    return NULL;
}

void* writer() {
    while (1) {
        lock(&tot);
        if (nb_write <= 0) {
            unlock(&tot);
            break;
        }
        nb_write--;  
        unlock(&tot);

        lock(&wmutex);
        wcount++;
        if (wcount == 1) locksem(&rsem); 
        unlock(&wmutex);

        locksem(&wsem);  
        data();  
        unlocksem(&wsem);  

        lock(&wmutex);
        wcount--;
        if (wcount == 0) unlocksem(&rsem);  
        unlock(&wmutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int nb_writer = atoi(argv[1]);
    int nb_reader = atoi(argv[2]);

    initsem(&rsem, 1);
    initsem(&wsem, 1);

    pthread_t writers[nb_writer];
    pthread_t readers[nb_reader];

    for (int i = 0; i < nb_writer; i++) pthread_create(&writers[i], NULL, writer, NULL);
    for (int i = 0; i < nb_reader; i++) pthread_create(&readers[i], NULL, reader, NULL);
    
    for (int i = 0; i < nb_writer; i++) pthread_join(writers[i], NULL);
    for (int i = 0; i < nb_reader; i++) pthread_join(readers[i], NULL);

    return 0;
}
