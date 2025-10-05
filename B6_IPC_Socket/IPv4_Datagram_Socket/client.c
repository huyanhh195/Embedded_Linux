#include "utils.h"

int client_fd = 0;

struct sockaddr_in server_addr;
socklen_t          len_server_addr = sizeof(server_addr);

int main(int argc, char *argv[])
{
    pthread_t thread_recv;
    pthread_t thread_send;

    if (argc != 2)
    {
        LOG_ERROR("Usage: %s <port_numer>", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signal_handler);

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port        = htons(atoi(argv[1]));

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0)
    {
        LOG_ERROR("Socket create failed");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("UDP socket created");

    pthread_create(&thread_recv, NULL, handle_recv_thread, NULL);
    pthread_create(&thread_send, NULL, handle_send_thread, NULL);

    while (flag_running)
    {
        msleep(100);
    }

    pthread_join(thread_recv, NULL);
    pthread_join(thread_send, NULL);

    close(client_fd);

    LOG_INFO("Client terminated");

    return 0;
}

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        cnt_signal++;
        if (cnt_signal > 1)
        {
            close(client_fd);

            exit(0);
        }

        flag_running = 0;
    }
}

void *handle_recv_thread(void *arg)
{
    char buf[1024];

    while (flag_running)
    {
        int n = recvfrom(client_fd,
                         buf,
                         sizeof(buf),
                         0,
                         (struct sockaddr *)&server_addr,
                         &len_server_addr);
        if (n > 0)
        {
            buf[n] = '\0';
            LOG_INFO("[CLIENT] Receive: %s", buf);

            if (strcmp(buf, "quit") == 0)
            {
                flag_running = 0;
            }
        }

        msleep(10);
    }

    return NULL;
}

void *handle_send_thread(void *arg)
{
    fd_set         rfds;
    struct timeval tv;

    char buf[1024];

    while (flag_running)
    {
        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);

        tv.tv_sec  = 0;
        tv.tv_usec = 100000;

        int ret = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(STDIN_FILENO, &rfds))
        {
            if (fgets(buf, sizeof(buf), stdin) != NULL)
            {
                size_t len = strlen(buf);
                if (len > 0 && buf[len - 1] == '\n')
                {
                    buf[len - 1] = '\0';
                }

                LOG_INFO("User input: %s", buf);

                sendto(client_fd,
                       buf,
                       strlen(buf),
                       0,
                       (struct sockaddr *)&server_addr,
                       len_server_addr);
            }
        }
    }

    return NULL;
}