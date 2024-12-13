#include "../include/fctsemaphore_TTS.h"

// Lock function using Test-and-Test-and-Set mechanism
#ifdef __x86_64__
    // x86_64 assembly code
    void lock(int* verou) {
        int etat = 1;
        asm(
            "all:\n\t"
            "testl %1, %0\n\t"   // Test if the lock is already acquired
            "jnz all\n\t"        // If the lock is acquired, jump to 'all' (retry)
            "enter:\n\t"
            "xchgl %1, %0\n\t"   // Exchange the values between *verou and etat
            "testl %1, %1\n\t"    // Test if the lock is successfully acquired
            "jnz enter\n\t"       // If not, retry
            : "+m"(*verou), "+r"(etat)
            :
        );
    }

    void unlock(int* verou) {
        asm(
            "movl $0, %0\n\t"   // Set *verou to 0 (release the lock)
            : "+m"(*verou)
            :
        );
    }

#elif defined(__aarch64__)
    // ARM64 assembly code
    void lock(int* verou) {
        if (verou == NULL) {
            fprintf(stderr, "Null pointer detected in lock\n");
            exit(EXIT_FAILURE);
        }

        int etat = 1;
        asm(
            "all:\n\t"
            "ldxr w1, [%x0]\n\t"        // Load *verou into w1
            "cbnz w1, all\n\t"           // If *verou != 0, retry (wait for lock to be released)
            "enter:\n\t"
            "stxr w1, %w2, [%x0]\n\t"   // Try to acquire the lock (set *verou to 1)
            "cbnz w1, all\n\t"           // If setting failed (lock still held), retry
            : "+r" (verou), "+r" (etat)   // Input-output operands
            : "r" (etat)                  // Additional input operand
            : "w1"                        // Clobbered register
        );
    }

    void unlock(int* verou) {
        if (verou == NULL) {
            fprintf(stderr, "Null pointer detected in unlock\n");
            exit(EXIT_FAILURE);
        }

        asm(
            "mov x1, #0\n\t"              // Set x1 to 0
            "str x1, [%x0]\n\t"           // Release the lock by setting *verou to 0
            : 
            : "r" (verou)                 // Input operand (pointer to lock)
            : "x1"                        // Clobbered register
        );
    }
#endif

void initsem(Semaphore* sem, int valeur_initiale) {
    sem->n = valeur_initiale;
    sem->verou = 0;  // Initialize as unlocked
}

void locksem(Semaphore* sem) {
    
    if (sem == NULL) {
        fprintf(stderr, "Null semaphore passed to locksem\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        lock(&sem->verou);  // Acquire the lock

        if (sem->n > 0) {   // If semaphore value > 0, acquire it
            sem->n--;
            unlock(&sem->verou);  // Release lock
            break;
        }

        unlock(&sem->verou);  // Release lock if not acquired
    }
}

void unlocksem(Semaphore* sem) {
    lock(&sem->verou);  // Acquire lock
    sem->n++;
    unlock(&sem->verou);  // Release lock
}
