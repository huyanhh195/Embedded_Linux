#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ARR_SIZE 1000000
#define STEP_SIZE (ARR_SIZE / 4)
#define I_AM_THREAD_0 0
#define I_AM_THREAD_1 1
#define I_AM_THREAD_2 2 
#define I_AM_THREAD_3 3
#define NUMBER_THREAD 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int idx = 0;
long sum = 0;
long sum_ref = 0;

typedef struct {
    int id;
    long *arr;
}thread_data_t;

void *funcThread(void *arg){
    pthread_mutex_lock(&lock);
    
    thread_data_t *data = (thread_data_t *)arg;
    pthread_t thread_id = pthread_self();
    
    if(data->id == I_AM_THREAD_0){
        for(int i = 0; i < STEP_SIZE; i++){
            sum += data->arr[i];
        }
    }
    else if(data->id == I_AM_THREAD_1){
        for(int i = STEP_SIZE; i < STEP_SIZE * 2; i++){
            sum += data->arr[i];
        }
    }
    else if(data->id == I_AM_THREAD_2){
        for(int i = STEP_SIZE * 2; i < STEP_SIZE * 3; i++){
            sum += data->arr[i];
        }
    }
    else if(data->id == I_AM_THREAD_3){
        for(int i = STEP_SIZE * 3; i < STEP_SIZE * 4; i++){
            sum += data->arr[i];
        }
    }

    pthread_mutex_unlock(&lock);
    return NULL;
}
int main(){
    long arr[ARR_SIZE] = {0};
    pthread_t thread[NUMBER_THREAD] = {0};
    thread_data_t data_thread[4] = {0};

    // sum reference
    for (long i = 0; i < ARR_SIZE; i++) {
        arr[i] = i;
        sum_ref += i;
    }

    for(int i = 0; i < 4; i++){
        data_thread[i].id = i;
        data_thread[i].arr = arr;
    }

    for(int i = 0; i < NUMBER_THREAD; i++){
        if(pthread_create(&thread[i], NULL, funcThread, &data_thread[i])){
            printf("Error creating thread %d\n", i);
            return 1;
        }
    }

    for(int i = 0; i < NUMBER_THREAD; i++){
        pthread_join(thread[i], NULL);
    }

    printf("======================================================================\n");
    printf("Sum Reference is: %ld\n", sum_ref);
    printf("Sum: %ld\n", sum);
    return 0;
}