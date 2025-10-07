#include "utils.h"

static bool running = ON;

socket_info_t socket_info = {0};

int main(int argc, char* argv[])
{
    pthread_t thread_connection;
    pthread_t thread_recv_msg;

    if (!init_logging(DEFAULT_LOG_PATH))
    {
        perror("Init logging failed");
        return -1;
    }

    log_debug("log file save at: %s", DEFAULT_LOG_PATH);

    if (argc != 2 || !check_valid_port(argv[1]))
    {
        log_error("Usage: %s <port>", argv[0]);
        return -1;
    }

    if (!init_socket(&socket_info, atoi(argv[1])))
    {
        log_error("Socket create failed");
        return -1;
    }

    pthread_create(
        &thread_connection, NULL, handle_connect_thread, &socket_info);
    pthread_create(
        &thread_recv_msg, NULL, handle_recv_msg_thread, &socket_info);

    show_help();

    while (running)
    {
        if (is_input_ready())
        {
            handle_input();
        }

        usleep(TIME_SLEEP);
    }

    log_info("Program will terminate");

    return 1;
}

bool is_input_ready()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval tv = {0, 0};
    int ret           = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0;

    return ret;
}

void handle_input()
{
    char buf[100];
    int  n = read(STDIN_FILENO, buf, sizeof(buf) - 1);

    if (n > 0)
    {
        buf[n] = '\0';
        if (buf[n - 1] == '\n') buf[n - 1] = '\0';

        log_debug("User entered: %s", buf);

        char* cmd_str = strtok(buf, " ");

        cmd_t cmd = string_to_cmd(cmd_str);

        switch (cmd)
        {
            case CMD_HELP:
                show_help();
                break;

            case CMD_MY_IP:
            {
                show_ip();

                break;
            }

            case CMD_MY_PORT:
                show_port();

                break;

            case CMD_CONNECT:
            {
                char* args = strtok(NULL, "");
                handle_cmd_connect(args);

                break;
            }

            case CMD_LIST:
            {
                show_list_connection();
                break;
            }

            case CMD_TERMINATE_IP:
            {
                char* args = strtok(NULL, "");
                handle_cmd_terminate(args);

                break;
            }

            case CMD_SEND_IP_MSG:
            {
                char* args = strtok(NULL, "");
                handle_cmd_send(args);
                break;
            }

            case CMD_EXIT:
            {
                log_debug("Exit command received");
                running = false;

                break;
            }

            default:
                log_warning("Unknown command: %s", cmd_str);
                show_help();

                break;
        }
    }
}

cmd_t string_to_cmd(const char* str)
{
    if (str == NULL) return CMD_UNKNOWN;

    if (strcmp(str, "help") == 0 || strcmp(str, "1") == 0) return CMD_HELP;
    if (strcmp(str, "myip") == 0 || strcmp(str, "2") == 0) return CMD_MY_IP;
    if (strcmp(str, "myport") == 0 || strcmp(str, "3") == 0) return CMD_MY_PORT;
    if (strcmp(str, "connect") == 0 || strcmp(str, "4") == 0)
        return CMD_CONNECT;
    if (strcmp(str, "list") == 0 || strcmp(str, "5") == 0) return CMD_LIST;
    if (strcmp(str, "terminate") == 0 || strcmp(str, "6") == 0)
        return CMD_TERMINATE_IP;
    if (strcmp(str, "send") == 0 || strcmp(str, "7") == 0)
        return CMD_SEND_IP_MSG;
    if (strcmp(str, "exit") == 0 || strcmp(str, "q") == 0 ||
        strcmp(str, "8") == 0)
        return CMD_EXIT;

    return CMD_UNKNOWN;
}

bool check_valid_port(const char* str_port)
{
    int tmp_port = atoi(str_port);

    for (const char* p = str_port; *p; p++)
    {
        if (!isdigit(*p))
        {
            log_error("Invalid port: %s", str_port);
            return false;
        }
    }

    if (tmp_port <= 0 || tmp_port > 65535)
    {
        log_error("Invalid port: %s", tmp_port);
        return false;
    }

    return true;
}

bool init_socket(socket_info_t* sock, int port)
{
    sock->addr.sin_family      = AF_INET;
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port        = htons(port);

    sock->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock->socket_fd < 0)
    {
        log_error("Socket create failed");
        exit(EXIT_FAILURE);
    }

    int ret = bind(
        sock->socket_fd, (struct sockaddr*)&sock->addr, sizeof(sock->addr));
    if (ret < 0)
    {
        log_error("Socket bind failed");
        close(sock->socket_fd);

        return false;
    }

    ret = listen(sock->socket_fd, MAX_PEER);
    if (ret < 0)
    {
        log_error("Socket listen failed");

        close(sock->socket_fd);
        return false;
    }

    log_info("App listening at port %d", ntohs(sock->addr.sin_port));

    return true;
}

void show_help()
{
    printf("-------------------------------------------------------");
    printf("\n|                  COMMAND LIST                       |");
    printf("\n-------------------------------------------------------");

    printf("\n1. help                show command list");
    printf("\n2. myip                show this app's IP address");
    printf("\n3. myport              show this app's listening port");
    printf("\n4. connect <ip> <port> connect to a remote peer");
    printf("\n5. list                list all active connections");
    printf("\n6. terminate <id>      close a connection by ID");
    printf("\n7. send <id> <msg>     send message to a connection");
    printf("\n8. exit                quit the application");

    printf("\n-------------------------------------------------------\n");
}

void show_ip()
{
    int          n;
    struct ifreq ifr;

    char array[] = "wlo1";

    n = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;

    strncpy(ifr.ifr_name, array, IFNAMSIZ - 1);

    ioctl(n, SIOCGIFADDR, &ifr);

    close(n);

    log_info(inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
}

void show_port()
{
    log_info("My port is: %d", ntohs(socket_info.addr.sin_port));
}

void* handle_connect_thread(void* arg)
{
    socket_info_t* sock = (socket_info_t*)arg;
    while (1)
    {
        if (sock->peer_count >= MAX_PEER)
        {
            log_warning("Max peers reached %d", MAX_PEER);

            msleep(500);

            continue;
        }

        peer_info_t* new_peer        = &sock->peer_list[sock->peer_count];
        socklen_t    len_client_addr = sizeof(new_peer->addr);

        new_peer->socket_fd = accept(sock->socket_fd,
                                     (struct sockaddr*)&new_peer->addr,
                                     &len_client_addr);
        if (new_peer->socket_fd < 0)
        {
            log_debug("Accept connection failed");

            msleep(100);

            continue;
        }
        log_critical("4");

        inet_ntop(AF_INET,
                  &new_peer->addr.sin_addr,
                  new_peer->ip,
                  sizeof(new_peer->ip));

        new_peer->port = ntohs(new_peer->addr.sin_port);

        new_peer->id = sock->peer_count;

        sock->peer_count++;

        log_info("Connected successfully");

        msleep(100);
    }

    return NULL;
}

void* handle_recv_msg_thread(void* arg)
{
    peer_info_t* peer = (peer_info_t*)arg;

    char buf[1024];

    // Set 200ms timeout to prevent blocking forever
    struct timeval tv = {0, 200000};
    setsockopt(peer->socket_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    while (1)
    {
        int n = recv(peer->socket_fd, buf, sizeof(buf) - 1, 0);
        if (n > 0)
        {
            buf[n] = '\0';
            log_info("[From %s:%d] %s", peer->ip, peer->port, buf);
        }

        msleep(10);
    }

    return NULL;
}

void msleep(int times)
{
    usleep(times * 1000);
}

void show_list_connection()
{
    log_warning("Connection: %d", socket_info.peer_count);
    for (int i = 0; i < socket_info.peer_count; i++)
    {
        printf("ID: %d\n", socket_info.peer_list[i].id);
        printf("IP: %s\n", socket_info.peer_list[i].ip);
        printf("Port: %d\n", socket_info.peer_list[i].port);
    }
}

void handle_cmd_connect(char* str)
{
    char* ip_str   = strtok(str, " ");
    char* port_str = strtok(NULL, "");

    if (ip_str == NULL || port_str == NULL)
    {
        log_warning("Usage: connect <ip> <port>");

        return;
    }

    if (!check_valid_port(port_str))
    {
        log_warning("Invalid port: %s", port_str);

        return;
    }

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port   = htons(atoi(port_str));
    inet_pton(AF_INET, ip_str, &client_addr.sin_addr);

    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0)
    {
        log_error("Socket create failed");

        exit(EXIT_FAILURE);
    }

    int ret =
        connect(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr));

    if (ret < 0)
    {
        log_info("Accept connection failed");

        close(client_fd);

        return;
    }

    peer_info_t* new_peer = &socket_info.peer_list[socket_info.peer_count];
    new_peer->socket_fd   = client_fd;
    new_peer->id          = socket_info.peer_count;
    new_peer->port        = atoi(port_str);
    strncpy(new_peer->ip, ip_str, sizeof(new_peer->ip));
    socket_info.peer_count++;

    log_info("Connected successfully");
}

void handle_cmd_terminate(char* str)
{
    char* id_str = strtok(str, " ");
    int   id     = atoi(id_str);

    log_debug("COunt: %d", socket_info.peer_count);

    if (id < 1 || id > (socket_info.peer_count + 1))
    {
        log_warning("Connection ID %d not found", id);
        return;
    }

    peer_info_t* peer = &socket_info.peer_list[id];
    close(peer->socket_fd);

    for (int i = id; i < socket_info.peer_count - 1; i++)
    {
        socket_info.peer_list[i] = socket_info.peer_list[i + 1];
    }

    socket_info.peer_count--;

    log_info("Peer ID %d disconnected", id);
}

void handle_cmd_send(char* str)
{
    if (str == NULL)
    {
        log_warning("Usage: send <id> <message>");
        return;
    }

    char* id_str  = strtok(str, " ");
    char* msg_str = strtok(NULL, "");

    if (id_str == NULL || msg_str == NULL)
    {
        log_warning("Usage: send <id> <message>");
        return;
    }

    int id = atoi(id_str);

    if (id < 0 || id >= socket_info.peer_count)
    {
        log_warning("Invalid peer ID: %d", id);
        return;
    }

    peer_info_t* peer = &socket_info.peer_list[id];

    int ret = send(peer->socket_fd, msg_str, strlen(msg_str), 0);
    if (ret < 0)
    {
        log_warning("Failed to send message to ID %d", id);
    }
    else
    {
        log_info("Message sent to ID %d successfully", id);
    }
}
