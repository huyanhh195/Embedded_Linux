#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
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
        write(socket_fd, "Hello from server\n", 20);
        sleep(1);
    }
}

int main(int argc, char *argv[]) {
    int port_no = 0;
    int socket_fd = 0;
    int new_socket_fd = 0;
    int ip = 0;
    struct sockaddr_un server_addr, client_addr;
    
    socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(socket_fd < 0 ){
        LOG_ERROR("Socket can't create\n");
    }
    LOG_INFO("Socket created");

    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH); 
    if(bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))){
        LOG_ERROR("Server can't bind\n");
    }
    
    if(listen(socket_fd, LISTEN_BACKLOG) < 0){
        LOG_ERROR("Server can't listen\n");
    }

    // LOG_INFO("Server started at ip %d port %d", ip,port_no);
    socklen_t client_len = sizeof(client_addr);
    while(1){
        new_socket_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &client_len);
        if (new_socket_fd < 0){
            LOG_ERROR("Server can't accept\n");
        }
        LOG_INFO("Client connected");
        handle_connection(new_socket_fd);
    }

    return 0;
}