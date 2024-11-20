#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/producerconsummer.h"

/**
 * Un mutex_prodcons pour bloquer l'accès au buffer 
 * Un sémaphore pour compter le nombre de cases du buffer remplies
 * Un sémaphore pour compter le nombre de cases du buffer vides
 */

// Variables initiales 
#define N 8
int buff[N];
int* buffer = buff;

int prodcount = 0;      // Garde un compte du nombre de producteur
int consumcount = 0;    // Garde un compte du nombre de consommateur


void process (){
    for (int i=0; i<10000; i++);
}

void* producer(void* arg){
    int* id = (int*)arg;
    static int ip = 0;  // Pour le buffer
    while(1){
        sem_wait(&cvides);
        pthread_mutex_lock(&mutex_prodcons);

        if (prodcount>=131072) // 131072
        {
            pthread_mutex_unlock(&mutex_prodcons);
            break;
        }
        
        // Section critique, écrire l'id du thread dans le buffer
        // On met l'incrémentation dans le même mutex_prodcons,
        // une idée de faire autrement c'est de rajouter un mutex_prodcons pour incrémenter cette variable
        // (un thread incrémentera en même temps qu'un autre produira ca peut etre pas mal)
        prodcount++; 
        buffer[ip] = *id;
        ip = (ip+1)%N;
        printf("Producer %d: prodcount=%d, ip=%d\n", *id, prodcount, ip);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cremplies);

    }
    return NULL;
}
// Parler dans le readme ou initialement que j'avais d'abord penser faire un while(1) if prodcount<10 : do else : break
// sans penser qu'en fait plusieurs threads vont verifier cette condition et acceder au bloc dans le if et donc ca va produire
// + que le seuil


// Garder le producer's id bien comme j'ai fait, mettre un compteur de consummer et producer et compter le nombre de fois
void* consummer(void* arg){
    static int ic = 0;
    while(1){
        sem_wait(&cremplies);
        pthread_mutex_lock(&mutex_prodcons);
        if (consumcount>=131072 && prodcount >= 131072) //131072
        {
            pthread_mutex_unlock(&mutex_prodcons);
            break;
        }
        
        // On lit ce qu'il y a dans le buffer (ici pour l'instant on ne fait rien)
        consumcount++;
        int element = buffer[ic];
        ic = (ic+1)%N;
        printf("Consumer: consumcount=%d, element=%d\n", consumcount, element);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cvides);
        
    }
    return NULL;
}
