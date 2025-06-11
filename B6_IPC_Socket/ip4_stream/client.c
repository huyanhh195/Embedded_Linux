#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h>

#define LOG_INFO(log)                   \
    do{                                 \
        printf("[INFO]: %s\n", log);    \
    }while(0)       

#define LOG_ERROR(log) \
    do{                                 \
        printf("[ERROR]: %s\n", log);   \
        exit(EXIT_FAILURE);             \
    }while(0)     

void handle_connection(int socket_fd){
    char buff_recv[100] = {0};
    char buff_send[100] = {0};
    while(1){
        read(socket_fd, buff_recv, sizeof(buff_recv));
        printf("[CLIENT]: %s\n", buff_recv);

        printf("[CLIENT]: ");
        fgets(buff_send, sizeof(buff_send), stdin);
        send(socket_fd, buff_send, sizeof(buff_send), 0);   

        // reset the buffer
        memset(buff_recv, 0, sizeof(buff_recv));
        memset(buff_send, 0, sizeof(buff_send));    
        sleep(1);
    }
}

int main(int argc, char *argv[]){
    int client_fd = 0;
    struct sockaddr_in server_addr;
    
    if (argc != 3){
        LOG_ERROR("Command is: ./client <ip> <port_numer>\n");
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0){
        LOG_ERROR("Can't create socket\n");
    }
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
            LOG_ERROR("Client can't connect\n");

    }

    while(1){
        LOG_INFO("Connected to server\n");
        handle_connection(client_fd);
    }
    return 0;
}