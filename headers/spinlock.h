#ifndef TAS_H
#define TAS_H

typedef struct spinlock{
    int locked; // 0 means free, 1 means locked
} spinlock_t;

// Same functions as mutex? 
void spinlock_init(spinlock_t **verou);
void spinlock_destroy(spinlock_t **verou);

void spinlock_lock(volatile spinlock_t **verou);
void spinlock_unlock(volatile spinlock_t **verou);

#endif