#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lockunlock.c"


int nb_thread;

// simulation de tarvail
void data() {
    for (int i = 0; i < 10000; i++);
}



void* testandset() {
    for (int i = 0; i < 32768/nb_thread; i++) {
        lock(&sem);
        counter++;   // Section critique
        unlock(&sem);
    }
}

int main(int argc, char* argv[]) {
    
    
    
    nb_thread = atoi(argv[1]);

    pthread_t threads[nb_thread];

    
    for (int i = 0; i < nb_thread; i++) pthread_create(&threads[i], NULL, testandset, NULL);
    
    for (int i = 0; i < nb_thread; i++) pthread_join(threads[i], NULL);
   
    printf("Final counter value: %d\n", counter);
    return 0;
}