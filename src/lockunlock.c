#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile int sem = 0;  
int counter = 0;       

void lock(volatile int* verou) {
    int etat = 1;
    while (etat){
        __asm__(
            "xchgl %1, %0\n\t"                       
            : "+m"(*verou), "+r"(etat)              
            :
        );
    }
}

void unlock(volatile int* verou) {
    int etat = 0;
    __asm__( 
        "xchgl %1, %0\n\t"       
        : "+m"(*verou), "+r"(etat)           
        :                     
    );
}