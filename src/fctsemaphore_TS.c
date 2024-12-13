#include "../include/fctsemaphore_TS.h"

// Lock function using Test-and-Set mechanism
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
            "enter:\n\t"
            "ldxr %w2, [%x0]\n\t"        // Charge *verou dans %w2
            "cbnz %w2, enter\n\t"         // Si *verou != 0, recommence (verrouillé)
            "stxr %w1, %w2, [%x0]\n\t"    // Essaye d'écrire 1 à *verou si non verrouillé
            "cbnz %w1, enter\n\t"         // Si l'écriture échoue, recommence
            : "+r"(*verou), "+r"(etat)    // Les registres utilisés
            : "r"(verou)
            : "%w1", "%w2"                // Registres utilisés dans l'asm
        );
    }

    void unlock(int* verou) {
        asm(
            "mov x1, #0\n\t"              // Met x1 à 0 (déverrouille)
            "str x1, [%x0]\n\t"           // Stocke 0 dans *verou
            : 
            : "r" (verou)
        );
    }

#endif

void initsem(Semaphore* sem, int valeur_initiale) {
    if (sem == NULL) {
        fprintf(stderr, "Null semaphore passed to initsem\n");
        exit(EXIT_FAILURE);
    }
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
    if (sem == NULL) {
        fprintf(stderr, "Null semaphore passed to unlocksem\n");
        exit(EXIT_FAILURE);
    }
    lock(&sem->verou);  // Acquire lock
    sem->n++;
    unlock(&sem->verou);  // Release lock
}