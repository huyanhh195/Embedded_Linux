#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SEND_COUNT        5
#define SEND_INTERVAL_SEC 2

mqd_t       message_queue;
const char* queue_name = "/my_queue";

int main(int argc, char* argv[])
{
    static int cnt = SEND_COUNT;

    if (argc != 3)
    {
        printf("Usage: %s <priority> <task_description>\n", argv[0]);
        return 1;
    }

    // Open a message queue
    message_queue = mq_open(queue_name, O_WRONLY, 0666, NULL);
    if (message_queue == -1)
    {
        perror("mq_open");
        return 1;
    }

    unsigned int message_priority = (unsigned int)atoi(argv[1]);
    const char*  task_description = argv[2];

    while (cnt)
    {
        if (mq_send(message_queue,
                    task_description,
                    strlen(task_description),
                    message_priority) == -1)
        {
            perror("mq_send");
            break;
        }

        cnt--;

        // 2 seconds interval between sends
        sleep(SEND_INTERVAL_SEC);
    }

    mq_close(message_queue);

    return 0;
}