#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include "fctsemaphore.c"


pthread_mutex_t rmutex;  
pthread_mutex_t wmutex;  
pthread_mutex_t z;
pthread_mutex_t tot;    

int* rsem;  
int* wsem;  

int rcount = 0; 
int wcount = 0; 

int nb_read = 2540;  
int nb_write = 640;  

// simulation de tarvail
void data() {
    for (int i = 0; i < 10000; i++);
}


// fonction reader
void* reader() {
    while (1) {
        
        // fini tout les read? / diminue le nombre de read a faire
        pthread_mutex_lock(&tot);
        if (nb_read <= 0) {
            pthread_mutex_unlock(&tot);
            break;
        }
        nb_read--;  
        pthread_mutex_unlock(&tot);


        // section critique : un read en cour
        pthread_mutex_lock(&z);
        //sem_wait(&rsem); 
        lock(rsem);
        pthread_mutex_lock(&rmutex);
        rcount++;
        // block les writer de commentcer tant que les reader n'on pas fini 
        if (rcount == 1) lock(wsem);//sem_wait(&wsem);
        pthread_mutex_unlock(&rmutex);
        //sem_post(&rsem);
        unlock(rsem);
        pthread_mutex_unlock(&z);


        // simulation de lecture
        data();  

        
        // section critique : un read fini
        pthread_mutex_lock(&rmutex);
        rcount--;
        // les reader qui on fini s'arrete et se retire de ceux qui sont en train de tourner
        if (rcount == 0) unlock(wsem);//sem_post(&wsem);
        pthread_mutex_unlock(&rmutex);
    }
    return NULL;
}


// fonction writer
void* writer() {
    while (1) {
        
        // fini tout les write? / diminue le nombre de write a faire
        pthread_mutex_lock(&tot);
        if (nb_write <= 0) {
            pthread_mutex_unlock(&tot);
            break;
        }
        nb_write--;  
        pthread_mutex_unlock(&tot);

        
        // section critique : un write en cour
        pthread_mutex_lock(&wmutex);
        wcount++;
        // block les read de recommentcer tant que le writer n'a pas fini 
        if (wcount == 1) lock(rsem);//sem_wait(&rsem); 
        pthread_mutex_unlock(&wmutex);

        
        // simulation d'écriture / bloque tout autre ecriture
        lock(wsem);//sem_wait(&wsem);  
        data();  
        unlock(wsem);//sem_post(&wsem);  

        
        // section critique : un write fini
        pthread_mutex_lock(&wmutex);
        wcount--;
        // le write se retir des writer actif et permet au reader de commencer
        if (wcount == 0) unlock(rsem);//sem_post(&rsem);  
        pthread_mutex_unlock(&wmutex);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    

    int nb_writer = atoi(argv[1]);
    int nb_reader = atoi(argv[2]);

    
    pthread_mutex_init(&rmutex, NULL);
    pthread_mutex_init(&wmutex, NULL);
    pthread_mutex_init(&z, NULL);
    pthread_mutex_init(&tot, NULL);

    //sem_init(&rsem, 0, 1);
    intitsem(&rsem);
    //sem_init(&wsem, 0, 1);
    intitsem(&wsem);

    pthread_t writers[nb_writer];
    pthread_t readers[nb_reader];


    for (int i = 0; i < nb_writer; i++) pthread_create(&writers[i], NULL, writer, NULL);
    for (int i = 0; i < nb_reader; i++) pthread_create(&readers[i], NULL, reader, NULL);
    
    for (int i = 0; i < nb_writer; i++) pthread_join(writers[i], NULL);
    for (int i = 0; i < nb_reader; i++) pthread_join(readers[i], NULL);

    destroysem(rsem);
    destroysem(wsem);

    return 0;
}
