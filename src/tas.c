#include "../headers/tas.h"



void spinlock_lock(volatile spinlock_t *lk){
//lk can only take 0 or 1 value
    int i = 1;
    while (i==1){
        asm(
        "xchg"

        );
    };
}