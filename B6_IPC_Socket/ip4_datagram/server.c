#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>

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


int handle_connection(int socket_fd){
    char buff_recv[100] = {0};
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    while (1){
        int recv_len = recvfrom(socket_fd, buff_recv, sizeof(buff_recv), 0, (struct sockaddr *)&client_addr, &client_len);
        if (recv_len > 0){
            sendto(socket_fd, "Hello from server\n", 20, 0, (struct sockaddr *)&client_addr, client_len);
    
        }
            
        sleep(1);
    }
    
}

int main(int argc, char *argv[]){
    int port_no = 0;
    int server_fd = 0, client_fd = 0;
    struct sockaddr_in server_addr, client_addr;

    if (argc < 2){
        LOG_ERROR("Command is: ./server <port_numer>\n");
    }
    else{
        port_no = atoi(argv[1]);
    }

    // Create address socket
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);

    server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_fd < 0){
        LOG_ERROR("Socket can't create\n");
    }

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        LOG_ERROR("Server can't bind\n");
    }

    LOG_INFO("UDP Server started");   
    while(1){
        handle_connection(server_fd);
    }
    close(server_fd);
    return 0;
}