#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int data = 0;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
pthread_t thread_read1 = 0, thread_read2 = 0, thread_read3 = 0, thread_read4 = 0, thread_read5 = 0;
pthread_t thread_write1 = 0, thread_write2 = 0;
    
void *funcRead(void *arg){
    pthread_rwlock_rdlock(&rwlock);
    pthread_t thread_id = pthread_self();
    if (pthread_equal(thread_id, thread_read1)){
        printf("Thread read 1 is reading\n"); 
    }
    else if (pthread_equal(thread_id, thread_read2)){
        printf("Thread read 2 is reading\n");
    }
    else if (pthread_equal(thread_id, thread_read3)){
        printf("Thread read 3 is reading\n");
    }
    else if (pthread_equal(thread_id, thread_read4)){
        printf("Thread read 4 is reading\n");
    }
    else if (pthread_equal(thread_id, thread_read5)){
        printf("Thread read 5 is reading\n");
    }
    printf("Read data: %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void *funcWrite(void *arg){
    pthread_rwlock_wrlock(&rwlock);
    pthread_t thread_id = pthread_self();
    if (pthread_equal(thread_id, thread_write1)){
        printf("Thread write 1 is writing\n");
    }
    else if (pthread_equal(thread_id, thread_write2)){
        printf("Thread write 2 is writing\n");
    }
    data++;
    printf("Write data: %d\n", data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}
int main(){

    // init r/w lock
    pthread_rwlock_init(&rwlock, NULL);

    // init threads
    if (pthread_create(&thread_read1, NULL, funcRead, NULL)){
        printf("Error creating thread read 1\n");
        return 1;
    }
    if (pthread_create(&thread_read2, NULL, funcRead, NULL)){
        printf("Error creating thread read 2\n");
        return 1;
    }
    if (pthread_create(&thread_read3, NULL, funcRead, NULL)){
        printf("Error creating thread read 3\n");
        return 1;
    }
    if (pthread_create(&thread_read4, NULL, funcRead, NULL)){
        printf("Error creating thread read 4\n");
        return 1;
    }
    if (pthread_create(&thread_read5, NULL, funcRead, NULL)){
        printf("Error creating thread read 5\n");
        return 1;
    }
    if (pthread_create(&thread_write1, NULL, funcWrite, NULL)){
        printf("Error creating thread write 1\n");
        return 1;
    }
    if (pthread_create(&thread_write2, NULL, funcWrite, NULL)){
        printf("Error creating thread write 2\n");
        return 1;
    }

    // wait for the threads to finish
    pthread_join(thread_read1, NULL);
    pthread_join(thread_read2, NULL);
    pthread_join(thread_read3, NULL);
    pthread_join(thread_read4, NULL);
    pthread_join(thread_read5, NULL);
    pthread_join(thread_write1, NULL);
    pthread_join(thread_write2, NULL);

    printf("Data: %d\n", data);

    return 0;
}