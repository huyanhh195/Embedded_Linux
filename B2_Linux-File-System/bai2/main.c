#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 

// function to handle write command
void handle_write_command(const char *file_name, const char *buff, int num ){
    // Create the fix path
    char path_file[100] = "bai2/";
    strcat(path_file, file_name);
    strcat(path_file, ".txt");

    // open a file 
    int fd = open(path_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    // printf("fd: %d\n", fd);
    if (fd == -1){
        printf("Can't open the file\n");
        return;
    }
    else
        printf("File open succesfull\n");

    int num_write = write(fd, buff, strlen(buff));
    // printf("num_write: %d\n", num_write);
    if (num_write == -1 ){
        printf("Can't write to file \n");
    }
    else{
        // printf("Number of bytes write: %d\n", num_write);
        printf("Write %s to file\n", buff);
    }

    // close the file
    close(fd);

}

// function to handle read command
int handle_read_command(const char *file_name, char *buff, int num ){
    // Create the fix path
    char path_file[100] = "bai2/";
    strcat(path_file, file_name);
    strcat(path_file, ".txt");
    // open a file 
    int fd = open(path_file, O_RDONLY); //Opens the file in read-only mode.
    // printf("fd: %d\n", fd);
    if (fd == -1){
        printf("File not exis\n");
        return 0;
    }
    else
        printf("File open succesfull\n");

    int er = read(fd, buff, num);
    if (er == -1){
        printf("Can't read frome file \n");
    }

    // close the file
    close(fd);

    return 1;
}


int main(int argc, char *argv[]){
    if (argc != 5){
        printf("Format command is: ./bin filename numb_bytes [r/w] \"Hello\"\n");
        printf("Please run again\n");
        return 1;
    }
    
    char *file_name = argv[1];
    int num_bytes = atoi(argv[2]);
    // printf("num: %d\n", num_bytes);
    char *command_rw = argv[3];
    char *buff = argv[4];

    if(*command_rw == 'r'){
        char buff[100] = {0};
        if (handle_read_command(file_name, buff, num_bytes)){
            printf("Data is: %s\n", buff);
        }
    }
    else if (*command_rw == 'w'){
        handle_write_command(file_name, buff, num_bytes);
    }
}