#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define TIME_DELAY 10

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

        printf("Child process: sleep 5s\n");
        sleep(5);

        printf("Child process: Running...\n");
        printf("Child procees: My pid is %d\n", getpid());
        printf("Child process: My pid parent is %d\n", getppid());

        for (int i = 0; i < TIME_DELAY; i++)
        {
            printf("Orphan process: Running...\n");

            sleep(1);
        }
    }

    else
    {
        printf("Parent process: Running...\n");

        printf("Parent process will terminate after 1s\n");
        sleep(1);
    }

    return 0;
}
