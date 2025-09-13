#include <signal.h>   // kill
#include <stdbool.h>  // bool
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // strcmp
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait
#include <unistd.h>     // fork

typedef enum mode
{
    MODE_NORMAL = 1,
    MODE_ABNORMAL
} mode_e;

bool string_to_mode(const char *str, int *mode);

int main(int argc, char *argv[])
{
    pid_t pid    = -1;
    int   status = 0;
    int   mode   = 0;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s mode_to_run\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!string_to_mode(argv[1], &mode))
    {
        fprintf(stderr, "Invalid mode. Use 'normal' or 'abnormal' \n");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0)
    {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("Child process:  My pid is %d\n", getpid());
        printf("Child process:  My parent pid is %d\n", getppid());
        if (mode == MODE_NORMAL)
        {
            exit(10);
        }
        else
        {
            while (true)
            {
                printf("Child process: Running...\n");
                sleep(1);
            }
        }
    }
    else
    {
        printf("Parent process: My pid is %d\n", getpid());
        printf("Parent process: My children pid is %d\n", pid);

        if (mode == MODE_ABNORMAL)
        {
            sleep(3);
            printf("Parent process: Terminating child process\n");
            kill(pid, SIGKILL);
        }

        wait(&status);

        if (WIFEXITED(status))
        {
            printf("Child process: Terminated normally with status: %d\n",
                   WEXITSTATUS(status));
        }
        else
        {
            printf("Child process: Terminated abnormally\n");
        }
    }
}

bool string_to_mode(const char *str, int *mode)
{
    if (str == NULL)
    {
        return false;
    }

    if (strcmp(str, "normal") == 0)
    {
        *mode = MODE_NORMAL;
    }
    else if (strcmp(str, "abnormal") == 0)
    {
        *mode = MODE_ABNORMAL;
    }
    else
    {
        return false;
    }

    return true;
}