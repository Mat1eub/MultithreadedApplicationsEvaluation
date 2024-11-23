#include <pthread.h>
#include <semaphore.h>
// github que un tuteur a donner pour voir comment sa marcher (resolution)
// https://gist.github.com/megaaa13/9fad5070cf79139a0be9b8c9a263fe5d

int rcount = 0;
int wcount = 0;

sem_t rsem ; 
sem_t wsem ; 

pthread_mutex_t rmutex;
pthread_mutex_t wmutex;
pthread_mutex_t z;


// simulation activiter proceseur
void data(){
    for (int i = 0; i < 10000; i++);
}

// reader
void* reader(){
    while(1){

        pthread_mutex_lock(&z);

        sem_wait(&rsem);

        // section critique
        pthread_mutex_lock(&rmutex);

        rcount++;
        if (rcount==1) sem_wait(&wsem); // arrivée du premier reader
        
        pthread_mutex_unlock(&rmutex);

        sem_post(&rsem);

        pthread_mutex_unlock(&z);


        //read_database();
        data();


        // section critique
        pthread_mutex_lock(&rmutex);

        rcount--;
        if(rcount==0) sem_post(&wsem); // départ du dernier reader
        
        pthread_mutex_unlock(&rmutex);
    }
}

//writer
void* writer(){
    while(1){

        // section critique
        pthread_mutex_lock(&wmutex);

        wcount++;
        if (wcount==1) sem_wait(&rsem); // arrivée du premier writer
        
        pthread_mutex_unlock(&wmutex);


        sem_wait(&wsem);

        //write_database();
        data();

        sem_post(&wsem);


        // section critique
        pthread_mutex_lock(&wmutex);
        
        wcount--;
        if(wcount==0) sem_post(&rsem); // départ du dernier writer
        
        pthread_mutex_unlock(&wmutex);
    }
    
}

int main(int argc, char const *argv[]){

    pthread_mutex_init(&rmutex, NULL);
    pthread_mutex_init(&wmutex, NULL);
    pthread_mutex_init(&z, NULL);

    int nb_writer = atoi(argv[1]);
    int nb_reader = atoi(argv[2]);

    pthread_t writers[nb_writer];
    pthread_t readers[nb_reader];

    // partie a reflechir
    sem_init(&rsem, 0, 1);
    sem_init(&wsem, 0, 1);
    // partie a reflechir


    for (int i = 0 ; i < nb_writer ; i++) pthread_create(&writers[i], NULL, writer, NULL);
    for (int i = 0 ; i < nb_reader ; i++) pthread_create(&readers[i], NULL, reader, NULL);

    for (int i = 0 ; i < nb_writer ; i++) pthread_join(writers[i], NULL);
    for (int i = 0 ; i < nb_reader ; i++) pthread_join(readers[i], NULL);
    
    
    return 0;
}