#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 

void write_to_file(const char *filename, const char *buffer){
    // open a file 
    int fd = open(filename, O_RDWR | O_EXCL | O_CREAT);
    // printf("fd: %d\n", fd);
    if (fd == -1){
        printf("Can't open\n");
    }
    else
        printf("File created succesfull\n");

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

// time ./bai2
// real    0m0.123s
// user    0m0.120s
// sys     0m0.003s
int main(){
    // 
    char buffer[50000 * 6] = {0};
    int offset = 0;

    for (int i = 1; i <= 50000; i++) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%d\n", i);
    }

    write_to_file("fileA.txt", buffer);
    write_to_file("fileB.txt", buffer);

}