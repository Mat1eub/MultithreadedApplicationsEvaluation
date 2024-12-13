#include "../include/fctsemaphore_TS.h"

void lock(int* verou) {
    int etat = 1;
    
    // Test-and-set locking mechanism
    __asm__(
        "enter:\n\t"            
        "xchgl %1, %0\n\t"          // Swap "etat" and "*verou"
        "testl %1, %1\n\t"          // Test if the lock is still held
        "jnz enter"                 // If the lock is still held jump to enter
        : "+m"(*verou), "+r"(etat)
        :
    );

}

void unlock(int* verou) {
    int etat = 0;
    __asm__( 
        "xchgl %1, %0\n\t"       
        : "+m"(*verou), "+r"(etat)           
        :                     
    );
}

void initsem(Semaphore* sem, int valeur_initiale) {
    sem->n = valeur_initiale;
    sem->verou = 0;             // Initiate the lock value to 0 (unlocked)
}

void locksem(Semaphore* sem) {
    while (1) {
        lock(&sem->verou);      // Acquire the lock for mutex

        // Check if sem counter is greater then 0
        if (sem->n > 0) { 
            sem->n--;     
            unlock(&sem->verou); 
            break;              // Exit the loop since the semaphore is acquired
        }

        unlock(&sem->verou);    // Release the lock if not greater then 0
    }
}

void unlocksem(Semaphore* sem) {
    lock(&sem->verou);   
    sem->n++;      
    unlock(&sem->verou); 
}

