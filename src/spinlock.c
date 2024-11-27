#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/spinlock.h"

// Fonction init il faut malloc
// Fonction destroy il faut free

void spinlock_lock(spinlock_t** verou) {
    __asm__(
        "enter:"
        "movl $1, %eax\n\t"     // Set the value of 1 in eax register (1 means locked)
        "xchgl %eax, %0\n\t"    // Exchange atomicly de value in eax and the value from *verou
        "testl %eax, %eax\n\t"  // if(eax==0) then ZF=0 
        "jnz enter\n\t"         // if ZF!=0 go back to enter
        : "+m"((*verou)->locked)
        :
    );

}

void spinlock_unlock(spinlock_t** verou) {
    __asm__(
            "movl $1, %eax\n\t"
            "xchgl %eax,%0\n\t"
            : "+m"((*verou)->locked)
            : 
            );
}

// Pourquoi le \n\t ? 
// Je metrai des commentaires sur pq on met un double pointeur
