#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void lock(int* verou) {
    __asm__(
        //"lock: \n\t"
        //".long 0 \n\t"
        "enter:\n\t"
        "movl $1, %eax\n\t"
        "xchgl %eax, %0\n\t"
        "testl %eax, %eax\n\t" 
        "jnz enter"   
        : "+m"(*verou)
        :
    );

}

void unlock(int* verou) {
    __asm__(
            "movl $1, %eax\n\t"
            "xchg %eax,%0\n\t"
            : "+m"(*verou)
            : 
            );
}