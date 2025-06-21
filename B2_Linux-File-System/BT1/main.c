#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 

int main(){
    const char buffer[] = "Hello Linux ";
    
    int fd = open("bai1.txt", O_APPEND | O_RDWR | O_CREAT, 0644);
    if (fd == -1){
        printf("Can't open\n");
    }
    else{
        printf("File open succesfull\n");
    }

    // move the cursor to the start of the file 
    lseek(fd, 100, SEEK_SET);

    int num_write = write(fd, buffer, strlen(buffer));
    if (num_write == -1 ){
        printf("Can't write to file \n");
    }
    else{
        printf("Number of bytes write: %d\n", num_write);
    }

    close(fd);
}