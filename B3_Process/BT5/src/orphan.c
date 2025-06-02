#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include <time.h>
#include <sys/wait.h>

#define TIME_DELAY 20

int main(){
    pid_t child_pid =0;

    child_pid = fork();

    if (child_pid >= 0){
        if (child_pid == 0){
            printf("Hello from children process with pid: %d and my parent have pid: %d\n", getpid(), getppid());
            sleep(5);
            printf("Hello from children process with pid: %d and my new parent have pid: %d\n", getpid(), getppid());

            for(int i =0; i < TIME_DELAY; i++){
                printf("Hello from orphan process\n");
                sleep(1);
            }
        }
        
        // parent process
        else{
            printf("Hello from parent process with pid: %d and my children have pid: %d\n", getpid(), child_pid);
            sleep(1);
        }
    }
    else{
        printf("Fork failed\n");
    }
    return 0;
}