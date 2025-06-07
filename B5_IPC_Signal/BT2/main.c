#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

#define ALARM_TIMES 1   

int time = 1;

// function handlng signal
void handleSingal(int signal){
    if (signal == SIGALRM){
        if(time > 10){
            printf("Time up!\nExiting...\n");
            exit(0);
        }
        printf("Timer: %d seconds\n", time);
        time += 1;
        alarm(ALARM_TIMES);
        
    }
    else if (signal == SIGINT) 
    {
        printf("Received SIGINT!\n");
        printf("Exiting...\n");
        exit(0);
    }
}

int main(){
    signal(SIGALRM, handleSingal);
    signal(SIGINT, handleSingal);
    alarm(ALARM_TIMES);

    while (1)
    {
        // printf("Running...\n");
        sleep(1);
    }
    // pause();
    return 0;
}