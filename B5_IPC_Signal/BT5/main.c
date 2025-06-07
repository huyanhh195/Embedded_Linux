#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/select.h>
#include<fcntl.h>
#include<string.h>

#define BUFSIZE 1024
const char *path = "BT5/data/output.txt";

void handleSingal(int sig){
    if (sig == SIGINT){
        printf("SIGINT received\n");
        // exit(0);
    }
    else if (sig == SIGTERM){
        printf("SIGTERM received\n");
        printf("The program will exit\n");
        exit(0);
    }
}

int main(){
    fd_set reading_fd;

    // register signal handler
    signal(SIGINT, handleSingal);
    signal(SIGTERM, handleSingal);
    FD_ZERO(&reading_fd);
    
    
    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    printf("File opened successfully\n");
    printf("The process have id: %d\n", getpid());

    while(1){
        FD_SET(fileno(stdin), &reading_fd);
        if (select(fileno(stdin)+1, &reading_fd, NULL, NULL, NULL)){
            char buffer[BUFSIZE]={0};
            if(fgets(buffer, sizeof(buffer), stdin)!= NULL){
                if(write(fd, buffer, strlen(buffer)) == -1){
                    printf("Error writing to file\n");
                    break;
                }
            }
            else{
                printf("Error reading from keyboard\n");
                break;
            }
        }
        sleep(1);
    }

    close(fd);
    return 0;
}