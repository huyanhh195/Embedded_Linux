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
    MODE_EXEC_LS,
    MODE_EXEC_DATE
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
        fprintf(stderr, "Invalid mode. Use 'ls' or 'date' \n");
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
        printf("Child process: Running...\n");
        sleep(2);

        if (mode == MODE_EXEC_LS)
        {
            execl("/bin/ls", "ls", "-l", (char *)NULL);
        }
        else
        {
            execl("/bin/date", "date", (char *)NULL);
        }

        perror("execl failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Parent process: Running...\n");

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

    if (strcmp(str, "ls") == 0)
    {
        *mode = MODE_EXEC_LS;
    }
    else if (strcmp(str, "date") == 0)
    {
        *mode = MODE_EXEC_DATE;
    }
    else
    {
        return false;
    }

    return true;
}