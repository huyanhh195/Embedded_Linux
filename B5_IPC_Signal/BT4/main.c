#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#define BUFSIZE 1024
const char *path_file = "./output.txt";

void handleSingal(int sig)
{
    if (sig == SIGINT)
    {
        printf("SIGINT received\n");
    }
    else if (sig == SIGTERM)
    {
        printf("SIGTERM received\n");
        printf("The program will exit\n");
        exit(0);
    }
}

int main()
{
    signal(SIGINT, handleSingal);
    signal(SIGTERM, handleSingal);

    fd_set reading_fd;
    FD_ZERO(&reading_fd);

    int fd = open(path_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    while (1)
    {
        FD_SET(fileno(stdin), &reading_fd);

        if (select(fileno(stdin) + 1, &reading_fd, NULL, NULL, NULL))
        {
            char buffer[BUFSIZE] = {0};

            if (fgets(buffer, sizeof(buffer), stdin) != NULL)
            {
                printf("User entered: %s", buffer);

                if (write(fd, buffer, strlen(buffer)) == -1)
                {
                    printf("Error writing to file\n");
                    break;
                }
            }
            else
            {
                printf("Error reading from keyboard\n");
                break;
            }
        }

        sleep(1);
    }

    close(fd);

    return 0;
}