#include <semaphore.h>
#include <stdlib.h>
#include "../headers/producerconsummer.h"

/* Un mutex pour bloquer l'accès au buffer 
 * Un sémaphore pour compter le nombre de cases du buffer remplies
 * Un sémaphore pour compter le nombre de cases du buffer vides
*/

// Variables initiales 
#define N 8
int buff[N];
int* buffer = &buff;

pthread_mutex_t mutex; // Mutex pour le buffer
sem_t clibres; // Compte les cases libres pour le Producteur
sem_t cremplies; // Compte les cases remplies pour le Consommateur


void* producer(void* arg){
    int* id = (int*)arg; // Est-ce que faire ça, ça crée bien un pointeur 'id' vers l'adresse mémoire où se trouve arg ?
    static int ip = 0;  // Pour le buffer
    while(1){
        sem_wait(&clibres);
        pthread_mutex_lock(&mutex);

        // Section critique, écrire l'id du thread dans le buffer
        buffer[ip] = *id;
        ip = (ip+1)%N;
        
        pthread_mutex_unlock(&mutex);
        sem_post(&cremplies);
    }
    return NULL;
}
