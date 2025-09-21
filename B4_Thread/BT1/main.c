#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_COUNT 2

typedef struct
{
    int data;  // data to be log
    int loop;  // interations
} thread_data_t;

void* log_thread_func(void* arg)
{
    thread_data_t* thread_data = (thread_data_t*)arg;

    int data = thread_data->data;
    int loop = thread_data->loop;

    for (int i = 0; i < loop; i++)
    {
        printf("Thread %lu: data = %d\n", pthread_self(), data);
        data++;
        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t     thread_id[THREAD_COUNT];
    thread_data_t thread_data[THREAD_COUNT];

    thread_data[0].data = 0;
    thread_data[0].loop = 10;
    thread_data[1].data = 100;
    thread_data[1].loop = 5;

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (pthread_create(
                &thread_id[i], NULL, &log_thread_func, &thread_data[i]))
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (pthread_join(thread_id[i], NULL))
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    return 0;
}
