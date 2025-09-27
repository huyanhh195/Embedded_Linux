#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ALARM_TIMES 1
#define ON          1
#define OFF         0

static int time        = 1;
static int flag_enable = OFF;

void handleSingal(int signal)
{
    if (signal == SIGALRM)
    {
        printf("Timer: %d seconds\n", time);
        if (time >= 10)
        {
            printf("Time up!\n");
            printf("Exiting...\n");

            exit(0);
        }

        time += 1;

        if (flag_enable)
        {
            alarm(ALARM_TIMES);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage:%s <flag>\n", argv[0]);
        return -1;
    }

    if (argc == 2 &&
        (strcmp(argv[1], "--enable") == 0 || strcmp(argv[1], "-e") == 0))
    {
        flag_enable = ON;
    }

    signal(SIGALRM, handleSingal);
    alarm(ALARM_TIMES);

    while (1)
    {
        sleep(5);
        printf("Running...\n");
    }

    return 0;
}