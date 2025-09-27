#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int cnt_signal = 1;

void signal_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Child received signal from parent %d\n", cnt_signal);

        if (cnt_signal >= 5)
        {
            printf("Chilld will terminate\n");
            exit(0);
        }

        cnt_signal++;
    }
}
int main()
{
    pid_t child_pid = -1;

    printf("Program running...\n");

    child_pid = fork();
    if (child_pid < 0)
    {
        perror("Fork failed\n");
    }

    if (!child_pid)
    {
        signal(SIGUSR1, signal_handler);
        while (1)
        {
            printf("Child running...\n");
            sleep(1);
        }

        exit(0);
    }

    while (1)
    {
        sleep(2);

        printf("Parent send signal\n");
        kill(child_pid, SIGUSR1);

        int   status;
        pid_t result = waitpid(child_pid, &status, WNOHANG);
        if (result == child_pid)
        {
            printf("Program will terminate\n");
            break;
        }
    }

    return 0;
}