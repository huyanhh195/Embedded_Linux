#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include <time.h>
#include <sys/wait.h>

// return random value EXIT_SUCCESS(0) or EXIT_FAILURE(1)
int return_random_status(){
    srand(time(NULL));

    int value = rand() % 2;

    printf("The children process return value: %d\n", value);

    return value;
}

int main(){
    pid_t child_pid =0;

    child_pid = fork();

    if (child_pid >= 0){
        if (child_pid == 0){
            printf("Hello from the children process!\n");
            
            #ifdef USE_SIGKILL
            while (1)
            {
                printf("The process children is running with pid: %d\n", getpid());

                sleep(1);
            }
            #endif
            
            int status = return_random_status();
            
            exit(status);
        }
        
        else{
            int status = 0;
            
            printf("Hello from the parent process!\n");
            printf("Waiting for the children process!\n");
            printf("=====================================\n");

            wait(&status);
            
            // Check the exit status 1 if the children process terminated normally
            if(WIFEXITED(status)){
                int exit_status =  WEXITSTATUS(status);

                printf("The children process terminated normally with exit status: %d\n", exit_status);
            }
            else{
                printf("The children process terminated abnormally\n");
            }
        }
    }
    else{
        printf("Fork failed\n");
    }

    return 0;
}