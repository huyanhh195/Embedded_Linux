#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define ARR_SIZE 100
#define ODD_MODE 1
#define EVEN_MODE 2

int odd_cnt = 0;
int even_cnt = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int mode;
    int *arr;
}thread_data_t;

void createArrRandomNumber(int *arr, int size){
    srand(time(NULL));

    for(int i = 0; i < size; i++){
        arr[i] = rand() %  100 + 1;
    }
}

void printArr(int *arr, int size){
    printf("Array: ");
    
    for(int i = 0; i < ARR_SIZE; i++){
        printf("%d ", arr[i]);
    }

    printf("\n***********************************************************************\n");
}

void *count_numbers_thread(void *arg){
    thread_data_t *ptr = (thread_data_t *)arg;

    switch (ptr->mode)
    {
        case ODD_MODE:
            for(int i = 0; i < ARR_SIZE; i++){
                if(ptr->arr[i] % 2 == 1){
                    odd_cnt++;
                }
            }
            break;

        case EVEN_MODE:
            for(int i = 0; i < ARR_SIZE; i++){
                if(ptr->arr[i] % 2 == 0){
                    even_cnt++;
                }
            }
            break;

        default:
            printf("Invalid mode\n");
            break;
    }

    return NULL;
}

int main(){
    int arr[ARR_SIZE]= {0};
    pthread_t odd_thread = 0, even_thread = 0;
    thread_data_t thread_odd_data = {0};
    thread_data_t thread_even_data = {0};

    thread_odd_data.mode = ODD_MODE;
    thread_even_data.mode = EVEN_MODE;
    thread_odd_data.arr = arr;
    thread_even_data.arr = arr;

    createArrRandomNumber(arr, ARR_SIZE);
    printArr(arr, ARR_SIZE);

    if(pthread_create(&odd_thread, NULL, count_numbers_thread, &thread_odd_data)){
        printf("Error creating odd thread\n");
        return 1;
    }

    if(pthread_create(&even_thread, NULL, count_numbers_thread, &thread_even_data)){
        printf("Error creating odd thread\n");
        return 1;
    }

    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);
    printf("Joined threads\n");

    printf("Odd count: %d\n", odd_cnt);
    printf("Even count: %d\n", even_cnt);
    printf("\n");
    
    return 0;   
}