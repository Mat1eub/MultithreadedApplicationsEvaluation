#ifndef TAS_H
#define TAS_H

typedef struct spinlock{
    int locked; // 0 means free, 1 means locked
} spinlock_t;

/**
 * @brief Spinlock version of pthread_mutex_init.
 * 
 * Initiate a lock for the threads by allocating it in the heap.
 * 
 * @param lk: Lock to be initiated.
 * @return 0 if success, 1 if there is a memory allocation error.
 * 
 */
int spinlock_init(spinlock_t **lk);
int spinlock_destroy(spinlock_t *lk);

void spinlock_lock(volatile spinlock_t *lk);
void spinlock_unlock(volatile spinlock_t *lk);

#endif