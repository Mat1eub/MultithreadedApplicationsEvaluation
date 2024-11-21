#include <pthread.h>

// https://gist.github.com/megaaa13/9fad5070cf79139a0be9b8c9a263fe5d

void data();

int rcount = 0;
int wcount = 0;
sem_t rsem ; // un seul 
sem_t wsem ; 

pthread_mutex_t rmutex;
pthread_mutex_t wmutex;

int main(){
    sem_init(&rsem, 0, 1);
    sem_init(&wsem, 0, 1);
}


//writer
void writer(){
    while(true){

        data();

        // section critique
        pthread_mutex_lock(&wmutex);
        wcount++;
        if (wcount==1)
        { // arrivée du premier writer
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&wmutex);


        sem_wait(&wsem);
        sem_post(&wsem);


        // section critique
        pthread_mutex_lock(&wmutex);
        wcount--;
        if(wcount==0)
        { // départ du dernier writer
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&wmutex);

        process_data();
    }
    
}

// reader
void reader(){
    while(true){

        sem_wait(&rsem);


        // section critique
        pthread_mutex_lock(&rmutex);
        rcount++;
        if (rcount==1)
        { // arrivée du premier reader
        sem_wait(&wsem);
        }
        pthread_mutex_unlock(&rmutex);


        sem_post(&rsem);
        read_database();


        // section critique
        pthread_mutex_lock(&rmutex);
        rcount--;
        if(rcount==0)
        { // départ du dernier reader
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&rmutex);

        process_data();
    }
}