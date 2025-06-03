#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_COUNTER 1000000

int counter = 0;
pthread_mutex_t mutex;

void *funcThread(void *arg){
    pthread_mutex_lock(&mutex);
    for(int i =0; i < NUMBER_COUNTER; i++)
        counter++;
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(){
    pthread_t thread1 = 0, thread2 = 0, thread3 = 0;
    
    printf("Counter before create thread: %d\n", counter);

    // Initialize a mutex
    if(pthread_mutex_init(&mutex, NULL)){
        printf("Error initializing mutex\n");
        return 1;
    }

    // Initialize a mutex static    
    // pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    // crete 3 threads
    if (pthread_create(&thread1, NULL, funcThread, NULL)){
        printf("Error creating thread 1\n");
        return 1;
    }
    if (pthread_create(&thread2, NULL, funcThread, NULL)){
        printf("Error creating thread 2\n");
        return 1; 
    }
    if (pthread_create(&thread3, NULL, funcThread, NULL)){
        printf("Error creating thread 3\n");
        return 1; 
    }

    // wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);    
    pthread_mutex_destroy(&mutex);

    // print counter
    printf("Counter after create thread: %d\n", counter);
    return 0;
}