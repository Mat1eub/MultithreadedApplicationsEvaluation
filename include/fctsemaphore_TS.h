#ifndef FCTSEMAPHORE_TS_H
#define FCTSEMAPHORE_TS_H

// Struct definition for our semaphore
typedef struct {
    int n;       // Semaphore counter
    int verou;   // Lock variable
} Semaphore;

/**
 * @brief Acquires a test-and-set lock.
 * 
 * Uses a busy-wait loop to acquire the lock. The lock is only acquired when
 * the value of the lock variable becomes 0.
 * 
 * @param verou Pointer to the lock variable.
 */
void lock(int* verou);

/**
 * @brief Releases a test-and-set lock.
 * 
 * Sets the lock variable to 0 to release the lock, allowing other threads to acquire it.
 * 
 * @param verou Pointer to the lock variable.
 */
void unlock(int* verou);


/**
 * @brief Initializes a semaphore.
 * 
 * Sets the initial count and initializes the lock variable to an unlocked state.
 * 
 * @param sem Pointer to the semaphore structure.
 * @param initial_value The initial value of the semaphore counter.
 */
void initsem(Semaphore* sem, int initial_value);

/**
 * @brief Acquires the semaphore.
 * 
 * Decrements the semaphore counter when it is greater than 0. If the counter is 0,
 * the calling thread will block (busy-wait) until the semaphore is available.
 * 
 * @param sem Pointer to the semaphore structure.
 */
void locksem(Semaphore* sem);

/**
 * @brief Releases the semaphore.
 * 
 * Increments the semaphore counter, signaling the availability of one resource.
 * 
 * @param sem Pointer to the semaphore structure.
 */
void unlocksem(Semaphore* sem);

#endif // FCTSEMAPHORE_TS_H
