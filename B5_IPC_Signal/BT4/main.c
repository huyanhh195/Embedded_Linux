#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void handleSingal(int signal){
    if(signal == SIGTSTP){
        printf("Received SIGTSTP!\n");
    }
}
int main(){
    signal(SIGTSTP, handleSingal);
    while(1){
        printf("Running...\n");
        sleep(1);
    }

    return 0;
}