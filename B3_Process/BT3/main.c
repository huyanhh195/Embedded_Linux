#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include <sys/wait.h>

#define CNT_TIMES 5

void handle_singal(int signal){
    if (signal == SIGUSR1){
        printf("Childen process received SIGUSR1!\n");
        
        #ifdef USE_EXEC
        printf("\n");
        execl("/usr/bin/free", "free", "-h", NULL);
        printf("\n");
        #endif
    }
}

int main(){
    pid_t child_pid =0;
    signal(SIGUSR1, handle_singal);

    child_pid = fork();

    if (child_pid >= 0){
        if (child_pid == 0){

            signal(SIGUSR1, handle_singal);
            
            while(1){
                sleep(1);
            }
        }    
        else{

            int cnt = 1;
            int status = 0;
            while(1){
                printf("Hello from the parent process!\n");
                
                sleep(1);

                // Enough CNT_TIMES will send signal
                cnt += 1;
                if(cnt % CNT_TIMES == 0) kill(child_pid, SIGUSR1);
            }
        }
    }
    else{
        printf("Fork failed\n");
    }

    return 0;
}