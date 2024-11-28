#include <stdio.h>
#include <stdlib.h>
#include "../headers/spinlock.h"

int spinlock_init(spinlock_t** lk){
    *lk = malloc(sizeof(spinlock_t));
    if(*lk==NULL){
        return 1; // Could not allocate correctly
    }
    (*lk)->locked = 0; // Initialization
    return 0; // Success
}

int spinlock_free(spinlock_t* lk){
    if(lk == NULL){
        return 1; // Nothing to free
    }
    free(lk);
    return 0; // Success
}

void spinlock_lock(spinlock_t* lk) {
    __asm__(
        "enter:"
        "movl $1, %eax\n\t"     // Set the value of 1 in eax register (1 means locked)
        "xchgl %eax, %0\n\t"    // Exchange atomicly de value in eax and the value from *lk
        "testl %eax, %eax\n\t"  // if(eax==0) then ZF=0 
        "jnz enter\n\t"         // if ZF!=0 go back to enter
        : "+m"(lk->locked)
        :
        :"eax"
    );

}

void spinlock_unlock(spinlock_t* lk) {
    __asm__(
            "movl $0, %eax\n\t" // (\n\t helps for the inline assembly nothing to understand really)
            "xchgl %eax,%0\n\t" // not $1 but $0 do wee need to still do an xchg or we could just do movl $0, %0 ?
            : "+m"(lk->locked)
            : 
            );
}
