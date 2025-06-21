#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_THREAD_READ 5
#define NUMBER_THREAD_WRITE 3

int data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t thread_read[NUMBER_THREAD_READ];
pthread_t thread_write[NUMBER_THREAD_WRITE];
    
void *funcRead(void *arg){
    pthread_rwlock_rdlock(&rwlock);

    int thread_num = *(int *)arg;
    pthread_t thread_id = pthread_self();
    
    printf("Reader thread %d is reading\n", thread_num + 1);
    printf("Read data: %d\n", data);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

void *funcWrite(void *arg){
    pthread_rwlock_wrlock(&rwlock);
    
    int thread_num = *(int *)arg;

    printf("Thread write %d is writing\n", thread_num + 1);
    data++;
    printf("Write data: %d\n", data);

    pthread_rwlock_unlock(&rwlock);

    return NULL;
}

int main(){

    pthread_rwlock_init(&rwlock, NULL);

    int read_thread_ids[NUMBER_THREAD_READ];
    int write_thread_ids[NUMBER_THREAD_WRITE];

    for(int i = 0; i < NUMBER_THREAD_READ; i++){
        read_thread_ids[i] = i + 1;

        if (pthread_create(&thread_read[i], NULL, funcRead, (void *)&read_thread_ids[i])){
            printf("Error creating thread read %d\n", i);
            return 1;
        }
    }

    for(int i = 0; i < NUMBER_THREAD_WRITE; i++){
        write_thread_ids[i] = i + 1;

        if (pthread_create(&thread_write[i], NULL, funcWrite, (void *)&write_thread_ids[i])){
            printf("Error creating thread write %d\n", i);
            return 1;
        }
    }

    for(int i = 0; i < NUMBER_THREAD_READ; i++){
        pthread_join(thread_read[i], NULL);
    }

    for(int i = 0; i < NUMBER_THREAD_WRITE; i++){
        pthread_join(thread_write[i], NULL);
    }

    printf("Data: %d\n", data);

    return 0;
}