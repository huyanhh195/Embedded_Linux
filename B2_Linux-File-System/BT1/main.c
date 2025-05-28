#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 


int main(){
    const char buffer[] = "Hello Linux ";
    // open a file 
    int fd = open("bai1/bai1.txt", O_APPEND | O_RDWR);
    // printf("fd: %d\n", fd);
    if (fd == -1){
        printf("Can't open\n");
    }
    else
        printf("File open succesfull\n");

    // move the cursor to the start of the file 
    lseek(fd, 100, SEEK_SET);
    int num_write = write(fd, buffer, strlen(buffer));
    // printf("num_write: %d\n", num_write);
    if (num_write == -1 ){
        printf("Can't write to file \n");
    }
    else{
        printf("Number of bytes writee: %d\n", num_write);
    }

    // close the file
    close(fd);

}