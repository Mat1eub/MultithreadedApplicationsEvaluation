#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <semaphore.h>

extern int N;
extern sem_t* forks;
void* philosopher(void* param);

#endif