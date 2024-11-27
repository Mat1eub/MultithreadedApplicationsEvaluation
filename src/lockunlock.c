#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     

void lock(int* verou) {
    int etat = 1;
    asm(
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
    asm( 
        "xchgl %1, %0\n\t"       
        : "+m"(*verou), "+r"(etat)           
        :                     
    );
}
