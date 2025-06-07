#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

#define CNT_SIGNAL 5
int cnt_receive_signal = 0;
// function handlng signal
void handleSingal(int signal){
    if(signal == SIGUSR1){
        printf("Received signal from parent\n");
        cnt_receive_signal += 1;
        if(cnt_receive_signal == CNT_SIGNAL){
            exit(0);
        }
    }
}

int main(){

    pid_t child_pid = 0;
    child_pid = fork();

    if (child_pid < 0){
        printf("Fork failed\n");
        return 1;
    }

    // child process
    if(child_pid == 0){
        signal(SIGUSR1, handleSingal);
        while (1)
        {
            sleep(1);
        }
        
    }

    // parent process
    if(child_pid > 0){
        while (1)
        {
            printf("Sending signal to children\n");
            kill(child_pid, SIGUSR1);
            sleep(2);
        }
        printf("Done\n");
    }
    return 0;
}