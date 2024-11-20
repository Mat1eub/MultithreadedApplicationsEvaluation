#ifndef PRODUCERCONSUMMER_H
#define PRODUCERCONSUMMER_H

extern pthread_mutex_t mutex_prodcons;  // Mutex for the buffer
extern sem_t cvides;           // Keeps track of the number of empty slot
extern sem_t cremplies;        // Keeps track of the number of full slot

/**
 * @brief Fonction exécutée par les threads producteurs
 * 
 * Cette fonction produit un élément et l'ajoute au buffer partagé
 * 
 * @param arg Pointeur vers l'identifiant unique du thread
 * @return NULL
 */
void* producer(void* arg);

/**
 * @brief Fonction exécutée par les threads consommateurs 
 * 
 * Lit un élément du buffer partagé
 * 
 * @param arg Argument passé au consommateur
 * @return NULL
 */
void* consummer(void* arg);


#endif //PRODUCERCONSUMMER_H