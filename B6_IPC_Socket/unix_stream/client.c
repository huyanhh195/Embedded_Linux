#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/un.h>
#define LOG_INFO(log)                   \
    do{                                 \
        printf("[INFO]: %s\n", log);    \
    }while(0)       

#define LOG_ERROR(log) \
    do{                                 \
        printf("[ERROR]: %s\n", log);   \
        exit(EXIT_FAILURE);             \
    }while(0)     
#define LISTEN_BACKLOG 50 
#define SOCKET_PATH "./socket"

void handle_connection(int socket_fd){
    while(1){
        char buff_send[100] = {0};
        // (socket_fd, "Hello from server\n", 20);
        read(socket_fd, buff_send, sizeof(buff_send));
        printf("[CLIENT]: %s", buff_send);
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    int port_no = 0;
    int socket_fd = 0;
    int ip = 0;
    struct sockaddr_un server_addr;

    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0 ){
        LOG_ERROR("Socket can't create\n");
    }
    LOG_INFO("Socket created");

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path));
    
    if(connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        LOG_ERROR("Client can't connect\n");
    }

    while(1){
        handle_connection(socket_fd);
    }

    return 0;
}