#include<stdio.h>
#include<unistd.h>

int main(){
    // decleare a variable
    int a = 5;
    pid_t child_pid = 0;

    printf("Program is running with PID; %d\n", getpid());
    
    // system call to create the child porcess
    pid_t child_pid = fork();

    switch (child_pid)
    {
    case 1:
        printf("In the parent process with PID: %d\n", getpid());
        break;
    case 0:
        printf("In the children process with PID: %d\n, my parent PID is: ", getpid(), getppid());
        break;
    case -1:
        printf("Fork failed\n");
        return 1; // Exit with an error code
        break;    
    default:
        break;
    }

}