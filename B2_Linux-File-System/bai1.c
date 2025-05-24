#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 


int main(){
    // 
    const char buffer[] = "Hello world\n";
    
    // open a file 
    int fd = open("filessystem.txt", O_RDWR | O_EXCL | O_CREAT);
    // printf("fd: %d\n", fd);
    if (fd == -1){
        printf("Can't open\n");
    }
    else
        printf("File created succesfull\n");

    // write to the file
    int num_write = write(fd, buffer, strlen(buffer));
    if (num_write == -1 ){
        printf("Can't write to file \n");
    }
    else{
        printf("Number of bytes writee: %d\n", num_write);
    }

    // close the file
    close(fd);

}