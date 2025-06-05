#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

// declare global variables
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data = 0;


// Create random number from 1 to 10
void createRandomNumber(int *data){
    srand(time(NULL));
    *data = rand() %  10 + 1;
    // printf("Random number: %d\n", *data);
}

void *funcProducer(void *arg){
    // acquire the lock
    pthread_mutex_lock(&lock);
    
    // create random number
    createRandomNumber(&data);
    printf("Producer created the number: %d\n", data);

    // notify the consumer
    pthread_cond_signal(&cond);

    // release the lock
    printf("Producer released the lock\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *funcConsumer(void *arg){
    // acquire the lock
    pthread_mutex_lock(&lock);

    printf("Consumer is waiting for the number\n");
    // wait for the signal
    pthread_cond_wait(&cond, &lock);

    printf("Consumer received the number: %d\n", data);

    // release the lock
    printf("Consumer released the lock\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){

    // create 2 threads
    pthread_t producer_thread = 0, consumer_thread = 0;
    if (pthread_create(&consumer_thread, NULL, funcConsumer, NULL)){
        printf("Error creating thread 2\n");
        return 1; 
    }
    // sleep(1);
    if (pthread_create(&producer_thread, NULL, funcProducer, NULL)){
        printf("Error creating thread 1\n");
        return 1;
    }

    // wait for the threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}