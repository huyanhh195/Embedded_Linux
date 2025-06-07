#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

#define CNT_RECEIVE 3
int cnt_receive_signal = 0;

  
// Handler for SIGINT, triggered by 
// Ctrl-C at the keyboard 
void handleSingal(int signal){
    if (signal == SIGINT){
        cnt_receive_signal += 1;
        printf("Received SIGINT %d times!\n", cnt_receive_signal);
    }
    if (cnt_receive_signal == CNT_RECEIVE)
        exit(0);
}

int main(){
    signal(SIGINT, handleSingal);
    while(1){
        printf("Running...\n");
        sleep(1);
    }
    return 0;
}