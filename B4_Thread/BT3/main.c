#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int data = 0;

// Create random number from 1 to 10
void createRandomNumber(int *data){
    srand(time(NULL));
    *data = rand() %  10 + 1;
}

void *producer_create_number(void *arg){
    pthread_mutex_lock(&lock);
    
    createRandomNumber(&data);
    printf("Producer created the number: %d\n", data);

    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&lock);
    printf("Producer released the lock\n");
    
    return NULL;
}

void *consumer_receive_number(void *arg){
    pthread_mutex_lock(&lock);

    printf("Consumer is waiting for the number\n");
    pthread_cond_wait(&cond, &lock);

    printf("Consumer received the number: %d\n", data);
   
    pthread_mutex_unlock(&lock);
    printf("Consumer released the lock\n");

    return NULL;
}

int main(){

    pthread_t producer_thread = 0, consumer_thread = 0;

    if (pthread_create(&consumer_thread, NULL, consumer_receive_number, NULL)){
        printf("Error creating thread 2\n");
        return 1; 
    }

    if (pthread_create(&producer_thread, NULL, producer_create_number, NULL)){
        printf("Error creating thread 1\n");
        return 1;
    }

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    return 0;
}