#include<stdio.h>
#include<unistd.h> 
#include <sys/wait.h>

int main(int argc, char *argv[]){
    if (argc < 2){
        printf("Please run again with format: %s <command_you_want>\n", argv[0]);

        return 1;
    }

    pid_t child_pid = 0;

    child_pid = fork();

    if (child_pid != -1){
        if (child_pid == 0){
            while(1){
                printf("In the children process\n");
                if(*argv[1] == '1'){
                    execlp("/usr/bin/ls", "ls", "-l", NULL);
                }
                else if (*argv[1] == '2')
                {
                    execlp("/usr/bin/date", "date", "-I", NULL);
                }
                else{
                    printf("No thing\n");
                }
                
                sleep(1);
            }

            while(1){
                printf("In the child process\n");

                sleep(1);
            }
            
        }
        else{
            int status = 0;

            while(1){
                printf("In the parent process\n");

                sleep(5);
            }
        }
    }

    return 0;
}