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
    pthread_t thread_0 = 0, thread_1 = 0, thread_2 = 0, thread_3 = 0;

    // Set array
    for (long i = 0; i < ARR_SIZE; i++) {
        arr[i] = i;
        sum_ref += i;
    }

    thread_data_t data_thread_0 = {0};
    thread_data_t data_thread_1 = {0};
    thread_data_t data_thread_2 = {0};
    thread_data_t data_thread_3 = {0};

    data_thread_0.id = I_AM_THREAD_0;
    data_thread_0.arr = arr;
    data_thread_1.id = I_AM_THREAD_1;
    data_thread_1.arr = arr;
    data_thread_2.id = I_AM_THREAD_2;
    data_thread_2.arr = arr;
    data_thread_3.id = I_AM_THREAD_3;
    data_thread_3.arr = arr;


    // Create 4 threads
    if(pthread_create(&thread_0, NULL, funcThread, &data_thread_0)){
        printf("Error creating thread 0\n");
        return 1;
    }
    if(pthread_create(&thread_1, NULL, funcThread, &data_thread_1)){
        printf("Error creating thread 1\n");
        return 1;
    }
    if(pthread_create(&thread_2, NULL, funcThread, &data_thread_2)){
        printf("Error creating thread 2\n");
        return 1;
    }
    if(pthread_create(&thread_3, NULL, funcThread, &data_thread_3)){
        printf("Error creating thread 3\n");
        return 1;
    }

    // wait for the threads to finish
    pthread_join(thread_0, NULL);
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    pthread_join(thread_3, NULL);

    printf("======================================================================\n");
    printf("Sum Reference is: %ld\n", sum_ref);
    printf("Sum: %ld\n", sum);
    return 0;
}