#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TIME_DELAY 2

int main()
{
    pid_t pid = 0;

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("Child process: Running...\n");
        printf("Child procees: My pid is %d\n", getpid());
        printf("Child process: My pid parent is %d\n", getppid());

        exit(0);
    }

    else
    {
        while (1)
        {
            printf("Parent process: Running...\n");

            sleep(TIME_DELAY);
        }
    }

    return 0;
}