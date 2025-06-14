#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
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
#define SOCKET_PATH "./socket"
#define HELLO_STRING "Hello from server"

int handle_connection(int socket_fd){
    char buff_recv[100] = {0};
    struct sockaddr_un client_addr;
    socklen_t client_len;

    while (1){
        memset(&client_addr, 0, sizeof(client_addr)); // FIXED
        client_len = sizeof(client_addr);

        int recv_len = recvfrom(socket_fd, buff_recv, sizeof(buff_recv), 0,(struct sockaddr *)&client_addr, &client_len);
        if (recv_len > 0){
            printf("[SERVER] Received: %s\n", buff_recv);
            sendto(socket_fd, HELLO_STRING, strlen(HELLO_STRING) + 1, 0,
                   (struct sockaddr *)&client_addr, client_len);
        } 
        sleep(1);
    }
}

int main(int argc, char *argv[]){
    int port_no = 0;
    int server_fd = 0;
    struct sockaddr_un server_addr;


    // Create address socket
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);
    unlink(SOCKET_PATH);

    server_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (server_fd < 0){
        LOG_ERROR("Server can't create socket\n");
    }

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        LOG_ERROR("Server can't bind\n");
    }

    LOG_INFO("Server started");
    while(1){
        handle_connection(server_fd);
    }
    close(server_fd);
    return 0;
}