#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define THREAD_COUNT   2
#define THEAD_PRODUCER 0
#define THEAD_CONSUMER 1

int             data       = 0;
int             data_ready = 0;
pthread_cond_t  cond_var   = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex      = PTHREAD_MUTEX_INITIALIZER;

// random data from 0 to 100
int random_data_func()
{
    return rand() % 100;
}

void *produce_data_func(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);

        while (data_ready)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }

        data = random_data_func();
        printf("Produced data %d: %d\n", i, data);

        data_ready = 1;
        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void *consume_data_func(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mutex);

        while (!data_ready)
        {
            pthread_cond_wait(&cond_var, &mutex);
        }

        printf("Consumed data %d: %d\n", i, data);

        data_ready = 0;
        pthread_cond_signal(&cond_var);

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    pthread_t threads[THREAD_COUNT];

    pthread_create(&threads[THEAD_PRODUCER], NULL, &produce_data_func, NULL);
    pthread_create(&threads[THEAD_CONSUMER], NULL, &consume_data_func, NULL);

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror("Failed to join thread");
            return 1;
        }
    }

    return 0;
}
