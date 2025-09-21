#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define THREAD_COUNT          3
#define INCREMENTS_PER_THREAD 1000000

typedef enum mode
{
    MODE_NO_MUTEX,
    MODE_MUTEX,
    MODE_COUNT
} mode_e;

mode_e          mode    = MODE_NO_MUTEX;
pthread_mutex_t mutex   = PTHREAD_MUTEX_INITIALIZER;
long long       counter = 0;

void *increase_counter_func(void *arg)
{
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++)
    {
        if (mode == MODE_MUTEX)
        {
            pthread_mutex_lock(&mutex);
            counter++;
            pthread_mutex_unlock(&mutex);
        }
        else
        {
            counter++;
        }
    }
}

mode_e string_to_mode(const char *str)
{
    if (strcmp(str, "mode_no_mutex") == 0)
        return MODE_NO_MUTEX;
    else if (strcmp(str, "mode_mutex") == 0)
    {
        return MODE_MUTEX;
    }
    return MODE_COUNT;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <chose_mode_to_run>\n", argv[0]);
        return 1;
    }

    mode = string_to_mode(argv[1]);
    if (mode == MODE_COUNT)
    {
        printf("Invalid mode. Available modes: mode_no_mutex, mode_mutex\n");
        return 1;
    }

    pthread_t threads[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (pthread_create(&threads[i], NULL, &increase_counter_func, NULL))
        {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < THREAD_COUNT; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror("Failed to join thread");
            return 1;
        }
    }

    printf("Final counter value: %lld\n", counter);

    return 0;
}
