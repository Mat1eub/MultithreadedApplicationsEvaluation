#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 8
// Detailed explaination in the README's Producters-Consummers section

// Initial variables
#define NB_ITEMS 131072
int buff[BUFFER_SIZE];
int* buffer = buff;

int prodcount = 0;      // Keeps track of the number of producer
int consumcount = 0;    // Keeps track of the number of consummer

int P;
int C;
pthread_mutex_t mutex_prodcons;
sem_t cvides;
sem_t cremplies;

void process (){
    for (int i=0; i<10000; i++);
}

void* producer(void* arg){
    int* id = (int*)arg;
    static int ip = 0;   // Indicates where we are in the buffer
    while(1){
        sem_wait(&cvides);
        pthread_mutex_lock(&mutex_prodcons);

        if (prodcount>=NB_ITEMS)
        {
            pthread_mutex_unlock(&mutex_prodcons);
            sem_post(&cremplies); // Point d'explication sur ça ?? Il faut y réfléchir et expliquer en une ligne ici et dans le readme que ca nous a posé executablee
            break;
        }
        
        // Critical section
        prodcount++; 
        buffer[ip] = *id;
        ip = (ip+1)%BUFFER_SIZE;
        printf("Producer %d: prodcount=%d, ip=%d\n", *id, prodcount, ip);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cremplies);

    }
    return NULL;
}

void* consummer(void* arg){
    static int ic = 0;
    while(1){
        sem_wait(&cremplies);
        pthread_mutex_lock(&mutex_prodcons);

        // Break condition : All products are consummed
        if (consumcount>=NB_ITEMS)
        {
            pthread_mutex_unlock(&mutex_prodcons);
            sem_post(&cvides); //j'avais oublié ca_
            break;
        }
        
        // Critical section
        consumcount++;
        int element = buffer[ic];
        ic = (ic+1)%BUFFER_SIZE;
        printf("Consumer: consumcount=%d, element=%d\n", consumcount, element);

        pthread_mutex_unlock(&mutex_prodcons);
        process();
        sem_post(&cvides);
    }
    return NULL;
}

int main(int argc, char const *argv[])
{ 
    const char* executable = argv[0];

    // make producersconsummers P=<number_of_producers> C=<number_of_consummers>
    if(strcmp(executable,"./producerconsummer_exec")==0){
        if(argc != 3){
            fprintf(stderr, "Usage: %s P=<number_of_producers> C=<number_of_consummers>\n",argv[0]);
        }
        // Get P&C from commande line
        P = atoi(argv[1]);
        C = atoi(argv[2]);
    }
    
    // make prodcons <total_number_of_threads>
    if(strcmp(executable,"./prodcons_graphs")==0){
        if (argc != 2){
            fprintf(stderr, "Usage: %s <total_number_of_threads>\n",argv[0]);
            return 1;
        }
        
        // Single argument: we split the threads
        int totalThreads = atoi(argv[1]);
        if (totalThreads <= 0) {
            fprintf(stderr, "Invalid total number of threads: %d\n", totalThreads);
            return 1;
        }

        // Even number of threads
        if(totalThreads%2==0){
            P = totalThreads/2;
            C = totalThreads/2;
        }else{ // Odd number of threads
            P = (totalThreads+1)/2;
            C = (totalThreads)/2;
        }
    }

    // Check if P and C are valid
    if (P <= 0) {
        fprintf(stderr, "Invalid number of producers.\n");
        return 1;
    }

    if (C <= 0) {
        fprintf(stderr, "Invalid number of consummers.\n");
        return 1;
    }

    // Initialization
    pthread_t producers[P];     // Threads for each producers
    int thread_id[P];
    pthread_t consummers[C];    // Threads for each consummers

    pthread_mutex_init(&mutex_prodcons, NULL);
    sem_init(&cvides,0,BUFFER_SIZE);
    sem_init(&cremplies,0,0);

    // Starting threads' work
    for (size_t i = 0; i < P; i++){
        thread_id[i]=i;
        pthread_create(&producers[i], NULL,producer,(void*)(&(thread_id[i])));
    }

    for (size_t i = 0; i < C; i++){
        pthread_create(&consummers[i], NULL,consummer,NULL);
    }
    
    // Threads' results
    for (int i = 0; i < P; i++) {
        pthread_join(producers[i], NULL);
    }
    for (int i = 0; i < C; i++) {
        pthread_join(consummers[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex_prodcons);
    sem_destroy(&cvides);
    sem_destroy(&cremplies);
    return 0;
}
