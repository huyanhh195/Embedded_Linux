#include "utils.h"

int server_fd = 0;

struct sockaddr_un server_addr;
struct sockaddr_un client_addr;
socklen_t          len_client_addr = sizeof(client_addr);

int main(int argc, char *argv[])
{
    pthread_t thread_recv;
    pthread_t thread_send;

    if (argc != 2)
    {
        LOG_ERROR("Usage: %s <path_socket>", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, signal_handler);

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, argv[1]);

    unlink(server_addr.sun_path);

    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_fd < 0)
    {
        LOG_ERROR("Socket create failed");

        exit(EXIT_FAILURE);
    }

    int ret =
        bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret < 0)
    {
        LOG_ERROR("Server bind failed");

        close(server_fd);

        exit(EXIT_FAILURE);
    }

    LOG_INFO("UDP server started at %s", server_addr.sun_path);

    pthread_create(&thread_recv, NULL, handle_recv_thread, NULL);
    pthread_create(&thread_send, NULL, handle_send_thread, NULL);

    while (flag_running)
    {
        msleep(100);
    }

    pthread_join(thread_recv, NULL);
    pthread_join(thread_send, NULL);

    close(server_fd);

    LOG_INFO("Server terminated");

    return 0;
}

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        cnt_signal++;
        if (cnt_signal > 1)
        {
            close(server_fd);

            exit(0);
        }

        flag_running = 0;
    }
}

void *handle_recv_thread(void *arg)
{
    char buf[1024];

    // Set 200ms timeout to prevent blocking forever
    struct timeval tv = {0, 200000};
    setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (flag_running)
    {
        int n = recvfrom(server_fd,
                         buf,
                         sizeof(buf),
                         0,
                         (struct sockaddr *)&client_addr,
                         &len_client_addr);

        if (n > 0)
        {
            buf[n] = '\0';
            LOG_INFO("[SERVER] Receive: %s", buf);
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

                sendto(server_fd,
                       buf,
                       strlen(buf),
                       0,
                       (struct sockaddr *)&client_addr,
                       len_client_addr);

                if (strcmp(buf, "quit") == 0)
                {
                    flag_running = 0;
                }
            }
        }
    }

    return NULL;
}