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

void handle_connection(int socket_fd){
    char buff_recv[100] = {0};
    char buff_send[100] = {0};
    while (1)
    {
        /* code */
        send(socket_fd, "Hello from server\n", 20, 0);

        read(socket_fd, buff_recv, sizeof(buff_recv));
        printf("[SERVER]: %s\n", buff_recv);
        sleep(1);
    }
    
}

int main(int argc, char *argv[]){
    int socket_fd = 0, new_socket_fd = 0;
    int port_no = 0;
    struct sockaddr_in server_addr, client_addr;
    
    if (argc < 2){
        LOG_ERROR("Command is: ./server <port_numer>\n");
    }
    else{
        port_no = atoi(argv[1]);
    }

    // Create address socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0){
        LOG_ERROR("Socket can't create\n");
    }


    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        LOG_ERROR("Server can't bind\n");
    }

    if(listen(socket_fd, LISTEN_BACKLOG) < 0){
        LOG_ERROR("Server can't listen\n");
    }
    
    int len = sizeof(client_addr);

    while(1){
        printf("Server is listening at port %d\n", port_no);
        
        new_socket_fd = accept(socket_fd,(struct sockaddr *) &client_addr, (socklen_t *)&len);
        if (new_socket_fd < 0){
            LOG_ERROR("Can't accept connection\n");
        }
        LOG_INFO("Connection accepted\n");
        handle_connection(new_socket_fd);

        // closing the connected socket
        close(new_socket_fd);
    }
    // closing the listening socket
    close(socket_fd);
    return 0;
}