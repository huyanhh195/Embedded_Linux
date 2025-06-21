#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_COUNTER 1000000
#define NUMBER_THREAD 3

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *increment_counter(void *arg){
    pthread_mutex_lock(&mutex);
    for(int i =0; i < NUMBER_COUNTER; i++)
        counter++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t thread[NUMBER_THREAD] = {0};
      
    printf("Counter before create thread: %d\n", counter);

    if(pthread_mutex_init(&mutex, NULL)){
        printf("Error initializing mutex\n");
        return 1;
    }

    for (int i = 0; i < NUMBER_THREAD; i++){
        if (pthread_create(&thread[i], NULL, increment_counter, NULL)){
            printf("Error creating thread 1\n");
            return 1;
        } 
    }

    // wait for the threads to finish
    for(int i = 0; i < NUMBER_THREAD; i++){
        pthread_join(thread[i], NULL);
    }

    printf("Counter after create thread: %d\n", counter);

    return 0;
}