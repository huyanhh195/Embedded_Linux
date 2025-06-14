#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <sys/un.h>

#define LISTEN_BACKLOG 50
#define LOG_INFO(log)                   \
    do{                                 \
        printf("[INFO]: %s\n", log);    \
    }while(0)       

#define LOG_ERROR(log) \
    do{                                 \
        printf("[ERROR]: %s\n", log);   \
        exit(EXIT_FAILURE);             \
    }while(0)      
#define SOCKET_PATH "./socket"    
#define CLIENT_SOCKET_PATH "./client_socket"
#define HELLO_STRING "Hello from client"

int handle_connection(int socket_fd, struct sockaddr_un *server_addr){
    char buff_recv[100] = {0};
    socklen_t server_len = sizeof( struct sockaddr_un);
    struct sockaddr_un temp_addr; 
    while(1)
    {
        sendto(socket_fd, HELLO_STRING, sizeof(HELLO_STRING), 0, (struct sockaddr*)server_addr, server_len);
        int recv_len = recvfrom(socket_fd, buff_recv, sizeof(buff_recv), 0, (struct sockaddr *)&temp_addr, &server_len);
        if (recv_len > 0){
            printf("[CLIENT]: %s\n", buff_recv);
        }
        sleep(1);
    }
    
}

int main(int argc, char *argv[]){
    int port_no = 0;
    int client_fd = 0;
    struct sockaddr_un server_addr, client_addr;

    // Create address socket
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    client_addr.sun_family = AF_UNIX;
    strncpy(client_addr.sun_path, CLIENT_SOCKET_PATH, sizeof(client_addr.sun_path) - 1);

    client_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (client_fd < 0){
        LOG_ERROR("Socket can't create\n");
    }
    unlink(CLIENT_SOCKET_PATH);
    if (bind(client_fd, (struct sockaddr*)&client_addr, sizeof(client_addr)) < 0) {
        LOG_ERROR("Client can't bind");
    }
    LOG_INFO("Client started");
    while(1){
        handle_connection(client_fd, &server_addr) ;
    }
    close(client_fd);
    return 0;
}