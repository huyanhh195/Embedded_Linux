#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int count_signal = 1;

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("SIGNINT received %d \n", count_signal);
        if (count_signal > 2)
        {
            exit(sig);
        }

        count_signal++;
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage:%s <flag>\n", argv[0]);
        return -1;
    }

    if (argc == 2 && (strcmp(argv[1], "--register_signal") == 0 ||
                      strcmp(argv[1], "-r") == 0))
    {
        signal(SIGINT, signal_handler);
    }

    while (1)
    {
        printf("Running...\n");

        sleep(1);
    }

    return 0;
}