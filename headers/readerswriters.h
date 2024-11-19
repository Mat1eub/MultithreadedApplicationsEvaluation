#ifndef READERSWRITERS_H
#define READERSWRITERS_H

#include <pthread.h>
#include <semaphore.h>

extern sem_t* access; // Grant access to the data base with semaphore 
extern int readcount; // Keeps track of how many readers are left on the data base
extern pthread_mutex_t mutex; // Mutex the readcount variable that will be modified by every reader

/**
 * @brief Function executed by a writer thread
 * 
 * This function allows a writer thread to access a shared database exclusively to make modifications. 
 * 
 * @param arg Pointer to an argument given to a thread (not used here i.e. NULL)
 * @return NULL
 */
void* writer(void* arg);

/**
 * @brief Function executed by a reader thread
 * 
 * This function allow a reader thread to access a shared database 
 * while ensuring that no writers modifies the database during reading.
 * 
 * @param arg Pointer to an argument given to a thread (not used here i.e. NULL)
 * @return NULL
 */
void* reader(void* arg);

#endif