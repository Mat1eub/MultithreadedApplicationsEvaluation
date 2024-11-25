#ifndef TAS_H
#define TAS_H

typedef struct spinlock{
    int locked;
} spinlock_t;

// Same functions as mutex? 
void spinlock_init(volatile spinlock_t *lk);
void spinlock_destroy(volatile spinlock_t *lk);

void spinlock_lock(volatile spinlock_t *lk);
void spinlock_unlock(volatile spinlock_t *lk);

#endif