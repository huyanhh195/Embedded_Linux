#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define PIPE_READ 0
#define PIPE_WRITE 1
#define MAX_SIZE 100
#define MAX_MSG 2

char *msg1 = "User: root";
char *msg2 = "Password: 123456";

void func(int signum)
{
    wait(NULL); 
    printf("Child process termination\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    char buffer[MAX_SIZE] = {0};
    char *msg[MAX_MSG] = {msg1, msg2};
    pid_t pid = 0;
    int fds[2] = {0};


    if (pipe(fds) < 0) {
        printf("Pipe can't create\n");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0){
        printf("In child process\n");
        int num_read  = 0;
        // close the pipe for writing
        close(fds[PIPE_WRITE]);

        // read the data from the pipe
        while (1)
        {
            num_read = read(fds[PIPE_READ], buffer, MAX_SIZE);
            if(num_read < 0){
                printf("Child process can't read from pipe\n");
                exit(1);
            }
            else if (num_read == 0){
                printf("Pipe end-of-pipe\n");
                break;
            }
            else{
                printf("Child process read %d bytes from pipe\n", num_read);
                printf("Child process read %d bytes from pipe\n", (int)strlen(buffer));
            }
        }

        // close the pipe for reading
        close(fds[PIPE_READ]);
    }
    else{
        // Prevent zombie process 
        signal(SIGCHLD, func);
        
        printf("In parent process\n");
        
        // close the pipe for reading
        if (close(fds[PIPE_READ])){
            printf("Parent process can't close pipe read\n");
            return 1;
        }

        // write the data to the pipe
        for (int i = 0; i < MAX_MSG; i++){
            if (write(fds[PIPE_WRITE], msg[i], strlen(msg[i]) + 1) < 0){
                printf("Parent process can't write to pipe\n");
                return 1;
            }
        }

        // close the pipe for writing
        close(fds[PIPE_WRITE]);
        
        while (1){
            sleep(1);
        }
        
    }

    printf("Main progcess exit...\n");
    return 0;
}