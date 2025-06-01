#include<stdio.h>
#include<unistd.h>


#define FORK_FAILED -1
#define CHILD_PROCESS 0
#define PARENT_PROCESS 1


int main(){
    // decleare a variable
    int a = 5;
    pid_t child_pid = 0;

    printf("Program is running with PID; %d\n", getpid());
    printf("----------------------------------------------------------------\n");

    // system call to create the child porcess
    child_pid = fork();

    if (child_pid != FORK_FAILED){
        // child process
        if (child_pid == CHILD_PROCESS){
            printf("In the children process with PID:%d \n", getpid());
            printf("The value of a in the children process: %d\n", --a);
            // while (1);
            
        }
        // parent process
        else{
            printf("In the parent process have child process with PID: %d\n", child_pid);
            printf("The value of a in the parent process: %d\n", ++a);

        }
    }
    else{
        printf("Fork failed\n");
        return 1;
    }

    return 0;
}