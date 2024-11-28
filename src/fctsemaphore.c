#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int intitsem(int** sem){
    *sem = malloc(sizeof(int));  // Allouer de la mémoire pour un int, pas pour un int*
    if (!*sem) {
        perror("malloc");
        return 1;
    }
    return 0;
}

void destroysem(int* verou){
    free(verou);
}

void lock(int* verou) {
    int etat = 1;
    
    __asm__(
        "enter:\n\t"
        "xchgl %1, %0\n\t"
        "testl %1, %1\n\t" 
        "jnz enter"                         
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
