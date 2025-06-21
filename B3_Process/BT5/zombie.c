#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

#define TIME_DELAY 2

int main(){
    pid_t child_pid =0;

    child_pid = fork();

    if (child_pid >= 0){
        if (child_pid == 0){
            printf("Hello from children process with pid: %d and my parent have pid: %d\n", getpid(), getppid());

            exit(0);
        }
        
        else{
            printf("Hello from parent process with pid: %d and my children have pid: %d\n", getpid(), child_pid);

            while (1)
            {
                printf("Hello from parent process with pid: %d and my children have pid: %d\n", getpid(), child_pid);

                sleep(TIME_DELAY);
            }
        }
    }
    else{
        printf("Fork failed\n");
    }

    return 0;
}