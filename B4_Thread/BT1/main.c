#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *funcThread1(void *arg){
    printf("Thread 1: Hello from thread\n");
    return NULL;
}
void *funcThread2(void *arg){
    printf("Thread 2: Hello from thread\n");
    return NULL;
}

int main(){
    pthread_t thread1 = 0, thread2 = 0;

    if (pthread_create(&thread1, NULL, funcThread1, NULL)){
        printf("Error creating thread 1\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, funcThread2, NULL)){
        printf("Error creating thread 2\n");
        return 1; 
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}