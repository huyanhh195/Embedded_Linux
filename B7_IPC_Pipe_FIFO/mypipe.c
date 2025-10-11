#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#define PID_LS_CMD     0
#define PID_WC_CMD     1
#define NUM_OF_PROCESS 2

#define FD_READ  0
#define FD_WRITE 1

void close_fd(int *fd)
{
    for (int i = 0; i < 2; i++)
    {
        close(fd[i]);
    }
}

int main()
{
    pid_t pid[NUM_OF_PROCESS];
    int   fd[2];

    if (pipe(fd) == -1)
    {
        perror("Pipe");

        return 1;
    }

    for (int i = 0; i < NUM_OF_PROCESS; i++)
    {
        pid[i] = fork();
        if (pid[i] < 0)
        {
            perror("Fork");

            return 1;
        }

        if (pid[i] == 0)
        {
            break;
        }
    }

    if (!pid[PID_LS_CMD])
    {
        dup2(fd[FD_WRITE], STDOUT_FILENO);

        close_fd(fd);

        execlp("ls", "ls", "-l", NULL);
    }
    else if (!pid[PID_WC_CMD])
    {
        dup2(fd[FD_READ], STDIN_FILENO);

        close_fd(fd);

        printf("Number of files: ");
        fflush(stdout);

        execlp("wc", "wc", "-l", NULL);
    }
    else
    {
        close_fd(fd);

        for (int i = 0; i < NUM_OF_PROCESS; i++)
        {
            wait(NULL);
        }
    }

    return 0;
}