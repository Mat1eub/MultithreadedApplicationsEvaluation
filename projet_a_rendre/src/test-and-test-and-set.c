#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int nb_thread;

int sem = 0;  

int counter = 0;  


void lock(int* verou) {
    int etat = 1;
    
    asm(
        "all:\n\t"
        "testl %1, %0\n\t" 
        "jnz all\n\t"
        "enter:\n\t"
        "xchgl %1, %0\n\t"
        "testl %1, %1\n\t" 
        "jnz enter\n\t"                         
        : "+m"(*verou), "+r"(etat)              
        :
    );

}

void unlock(int* verou) {
    asm( 
        "movl $0, %0\n\t"       
        : "+m"(*verou)          
        :                     
    );
}


// simulation de tarvail
void data() {
    for (int i = 0; i < 10000; i++);
}

void* testandset() {
    for (int i = 0; i < 32768/nb_thread; i++) {
        lock(&sem);
        data();
        counter++;   // Section critique / verification que ca marche
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