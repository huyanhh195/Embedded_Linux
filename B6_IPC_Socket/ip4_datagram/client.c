#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

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



int handle_connection(int socket_fd, struct sockaddr_in server_addr){
    char buff_recv[100] = {0};
    socklen_t server_len = sizeof(server_addr);
    while(1)
    {
        sendto(socket_fd, "Hello from client", 18, 0,
               (struct sockaddr*)&server_addr, server_len);
        int recv_len = recvfrom(socket_fd, buff_recv, sizeof(buff_recv), 0, (struct sockaddr *)&server_addr, &server_len);
        if (recv_len > 0){
            printf("[CLIENT]: %s\n", buff_recv);
        }
        sleep(1);
    }
    
}

int main(int argc, char *argv[]){
    int port_no = 0;
    int client_fd = 0;
    struct sockaddr_in server_addr, client_addr;

    if (argc < 3){
        LOG_ERROR("Command is: ./client <ip> <port_numer>\n");
    }
    else{
        port_no = atoi(argv[2]);
    }
    // Create address socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(port_no);

    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0){
        LOG_ERROR("Socket can't create\n");
    }

    LOG_INFO("UDP Client started");
    while(1){
        handle_connection(client_fd, server_addr) ;
    }
    close(client_fd);
    return 0;
}