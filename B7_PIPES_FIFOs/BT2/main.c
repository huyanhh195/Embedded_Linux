#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>


#define PIPE_READ 0
#define PIPE_WRITE 1
#define BUFFER_SIZE 100

char *msg = "Data: 0x12";
char *msg_add = "34";

void func(int signum)
{
    wait(NULL); 
    printf("Child process termination\n");
    exit(0);
}

int main(int argc, char *argv[]) {

    char buffer[BUFFER_SIZE] = {0};
    int fds_p_to_c1[2] = {0};
    int fds_c1_to_c2[2] = {0};
    int pid_c1 = 0;
    int pid_c2 = 0;

    // init pipe
    if (pipe(fds_p_to_c1) < 0) {
        printf("Pipe can't create\n");
        return 1;
    }
    if (pipe(fds_c1_to_c2) < 0) {
        printf("Pipe can't create\n");
        return 1;
    }

    // init process
    pid_c1 = fork();
    if (pid_c1 < 0) {
        printf("Fork failed\n");
        return 1;
    }
    pid_c2 = fork();
    if (pid_c2 < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid_c1 == 0) {
        int num_read  = 0;
        printf("In child 1 process\n");

        // close the pipe 
        close(fds_p_to_c1[PIPE_WRITE]);
        close(fds_c1_to_c2[PIPE_READ]);

        while (1)
        {
            num_read = read(fds_p_to_c1[PIPE_READ], buffer, BUFFER_SIZE);
            if(num_read < 0){
                printf("Child 1 process can't read from pipe\n");
                return 1;
            }
            else if (num_read == 0){
                printf("Pipe end of pipe\n");
                break;
            }
            else{
                printf("Child 1 process receive - %s\n", buffer);
                strcat(buffer, msg_add);

                // write to pipe child 1 to child 2
                printf("Child 1 process write - %s\n", buffer);
                if (write(fds_c1_to_c2[PIPE_WRITE], buffer, strlen(buffer)) < 0){
                    printf("Can't write to pipe\n");
                    return 1;
                }
            }
        }
    }

    if (pid_c2 == 0) {
        int num_read  = 0;
        printf("In child 2 process\n");

        // close the pipe 
        close(fds_c1_to_c2[PIPE_WRITE]);

        while (1)
        {
            num_read = read(fds_c1_to_c2[PIPE_READ], buffer, BUFFER_SIZE);
            if(num_read < 0){
                printf("Child 2 process can't read from pipe\n");
                return 1;
            }
            else if (num_read == 0){
                printf("Pipe end of pipe\n");
                break;
            }
            else{
                printf("Child 2 process receive - %s\n", buffer);
            }
        }
    }

    printf("In parent process\n");
    signal(SIGCHLD, func);

    if(close(fds_p_to_c1[PIPE_READ]) < 0){
        printf("Can't close pipe read of parent to child 1\n");
        return 1;
    }
    
    printf("Parent process write - %s\n", msg);
    if (write(fds_p_to_c1[PIPE_WRITE], msg, strlen(msg)) < 0){
        printf("Can't write to pipe\n");
        return 1;
    }

    while (1)
    {
        sleep(1);
    }
    
    return 0;
}