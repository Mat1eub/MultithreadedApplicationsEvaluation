#include "../include/fctsemaphore_TTS.h"

void lock(int* verou) {
    int etat = 1;
    
    asm(
        "all:\n\t"                  // Test the current value of the lock (verou)
        "testl %1, %0\n\t"          // If lock is 1 (set), jump to "all" and retry (busy-wait)
        "jnz all\n\t"
        "enter:\n\t"
        "xchgl %1, %0\n\t"
        "testl %1, %1\n\t" 
        "jnz enter\n\t"                         
        : "+m"(*verou), "+r"(etat)              
        :
    );

}

void unlock(int* verou) {
    asm( 
        "movl $0, %0\n\t"           // Unlock the lock without xchg 
        : "+m"(*verou)          
        :                     
    );
}

void initsem(Semaphore* sem, int valeur_initiale) {
    sem->n = valeur_initiale;
    sem->verou = 0; 
}

void locksem(Semaphore* sem) {
    while (1) {
        lock(&sem->verou); 

        //verifie que c'est ok
        if (sem->n > 0) { 
            sem->n--;     
            unlock(&sem->verou); 
            break;
        }

        unlock(&sem->verou); 
    }
}

void unlocksem(Semaphore* sem) {
    lock(&sem->verou);   
    sem->n++;      
    unlock(&sem->verou); 
}

