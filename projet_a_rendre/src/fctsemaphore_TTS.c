#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// meme lock unlock que test and test and set
void lock(int* verou) {
    int etat = 1;
    
    asm(
        "all:\n\t"
        "testl %1, %0\n\t" 
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
        "movl $0, %0\n\t"       
        : "+m"(*verou)          
        :                     
    );
}


// besoin d'unne base de donner
typedef struct {
    int n; 
    int verou;   
} Semaphore;

// init
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

    // on retire
    lock(&sem->verou);   
    sem->n++;      
    unlock(&sem->verou); 
}

