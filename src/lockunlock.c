#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void lock(int* verou) {
    int etat = 1; 
    while (etat == 1) {
        __asm__(
            "xchg %0, %1\n\t"   
            : "+m"(*verou), "+r"(etat) 
            :
        );
    }
}

void unlock(int* verou) {
    int etat = 1; 
    __asm__(
            "xchg $0,%0\n\t"
            : "+m"(*verou), "+r"(etat)
            : 
            );
}