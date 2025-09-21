#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define THREAD_READ_COUNT  5
#define THREAD_WRITE_COUNT 2

pthread_rwlock_t rw_lock = PTHREAD_RWLOCK_INITIALIZER;

int data = 0;

void *read_func(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 10; i++)
    {
        pthread_rwlock_rdlock(&rw_lock);

        printf("Thread reader %d read data: %d\n", id, data);

        pthread_rwlock_unlock(&rw_lock);

        sleep(1);
    }
    return NULL;
}

void *write_func(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 10; i++)
    {
        pthread_rwlock_rdlock(&rw_lock);

        printf("Thread writer %d write data %d\n", id, data);
        data++;

        pthread_rwlock_unlock(&rw_lock);

        sleep(1.5);
    }
    return NULL;
}

int main()
{
    pthread_t threads_read[THREAD_READ_COUNT];
    pthread_t threads_write[THREAD_WRITE_COUNT];

    int id_thread[THREAD_READ_COUNT > THREAD_WRITE_COUNT ? THREAD_READ_COUNT
                                                         : THREAD_WRITE_COUNT];

    for (int i = 0; i < THREAD_READ_COUNT; i++)
    {
        id_thread[i] = i + 1;

        if (pthread_create(&threads_read[i], NULL, &read_func, &id_thread[i]))
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_WRITE_COUNT; i++)
    {
        id_thread[i] = i + 1;

        if (pthread_create(&threads_write[i], NULL, &write_func, &id_thread[i]))
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_READ_COUNT; i++)
    {
        if (pthread_join(threads_read[i], NULL))
        {
            perror("Failed to join thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_WRITE_COUNT; i++)
    {
        if (pthread_join(threads_write[i], NULL))
        {
            perror("Failed to join thread");
            return 1;
        }
    }
    return 0;
}
