#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
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

pthread_mutex_t mutex_prodcons;  // Mutex pour le buffer
sem_t cvides;           // Compte les cases libres pour le Producteur
sem_t cremplies;        // Compte les cases remplies pour le Consommateur
int prodcount = 0;      // Garde un compte du nombre de producteur
int consumcount = 0;    // Garde un compte du nombre de consommateur


void process (){
    for (int i=0; i<10000; i++);
}

void* producer(void* arg){
    int* id = (int*)arg;
    static int ip = 0;  // Pour le buffer
    while(1){
        if (prodcount < 131072){
            sem_wait(&cvides);
            pthread_mutex_lock(&mutex_prodcons);

            // Section critique, écrire l'id du thread dans le buffer
            // On met l'incrémentation dans le même mutex_prodcons,
            // une idée de faire autrement c'est de rajouter un mutex_prodcons pour incrémenter cette variable
            // (un thread incrémentera en même temps qu'un autre produira ca peut etre pas mal)
            prodcount++; 
            buffer[ip] = *id;
            ip = (ip+1)%N;
            
            pthread_mutex_unlock(&mutex_prodcons);
            process();
            sem_post(&cremplies);
        }else
        {
            break;
        }   
    }
    return NULL;
}


// Garder le producer's id bien comme j'ai fait, mettre un compteur de consummer et producer et compter le nombre de fois
void* consummer(void* arg){
    static int ic = 0;
    while(1){
        sem_wait(&cremplies);
        pthread_mutex_lock(&mutex_prodcons);
        if (consumcount && prodcount >= 131072)
        {
            break;
        }
        
        // On lit ce qu'il y a dans le buffer (ici pour l'instant on ne fait rien)
        consumcount++;
        int element = buffer[ic];
        ic = (ic+1)%N;

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cvides);
        
    }
    return NULL;
}
