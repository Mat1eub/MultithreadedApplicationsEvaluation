#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/tas.h"

void spinlock_lock(int* verou) {
    __asm__(
        "enter:"
        "movl $1, %eax"     // Set the value of 1 in eax register (1 means locked)
        "xchgl %eax, %0"    // Exchange atomicly de value in eax and the value from *verou
        "testl %eax, %eax"  // if(eax==0) then ZF=0 
        "jnz enter"         // if ZF!=0 go back to enter
        : "+m"(*verou)
        :
    );

}

void spinlock_unlock(int* verou) {
    __asm__(
            "movl $1, %eax"
            "xchg %eax,%0"
            : "+m"(*verou)
            : 
            );
}