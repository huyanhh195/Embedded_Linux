#include <mqueue.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_handler(int signum);

mqd_t       message_queue;
const char* queue_name  = "/my_queue";
char*       buffer_recv = NULL;

int main(int argc, char* argv[])
{
    struct mq_attr attr;

    signal(SIGINT, signal_handler);

    // Set queue attribute
    attr.mq_flags   = 0;
    attr.mq_maxmsg  = 10;
    attr.mq_msgsize = 1024;

    // Open a message queue
    message_queue = mq_open(queue_name, O_CREAT | O_RDONLY, 0666, &attr);
    if (message_queue == -1)
    {
        perror("mq_open");
        return 1;
    }

    buffer_recv = (char*)malloc(attr.mq_msgsize);
    if (!buffer_recv)
    {
        perror("malloc");
        return 1;
    }

    printf("Task worker running...\n");

    while (1)
    {
        unsigned int message_priority;
        ssize_t      bytes_read;

        bytes_read = mq_receive(
            message_queue, buffer_recv, attr.mq_msgsize, &message_priority);

        if (bytes_read >= 0)
        {
            buffer_recv[bytes_read] = '\0';

            printf("Processing task (Priority: <%u>): %s\n",
                   message_priority,
                   buffer_recv);
        }
        else
        {
            perror("mq_receive");
            break;
        }

        switch (message_priority)
        {
            case 0:
                printf("Handling low priority task...\n");
                sleep(1);
                break;

            case 1:
                printf("Handling medium priority task...\n");
                sleep(1);
                break;

            case 2:
                printf("Handling high priority task...\n");
                sleep(1);
                break;

            default:
                printf("Not supported priority level!\n");
                break;
        }
    }

    return 0;
}

void signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        if (buffer_recv)
        {
            free(buffer_recv);
            buffer_recv = NULL;
        }

        mq_close(message_queue);

        mq_unlink(queue_name);

        printf("Program terminated.\n");

        exit(0);
    }
}
