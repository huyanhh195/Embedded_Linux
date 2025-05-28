#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>


int main(int argc, char *argv[])
{
    char *filename = "bai3/bai3.txt";

    // get file infor
    struct stat sb;

    if (stat(filename, &sb) == -1) {
        perror("Can't get file information");
        return 1;
    }

    char *file_type;    
    switch (sb.st_mode & S_IFMT) {
        case S_IFREG:
            file_type = "Regular file";
            break;
        case S_IFDIR:
            file_type = "Directory";
            break;
        case S_IFCHR:
            file_type = "Character device";
            break;
        case S_IFBLK:
            file_type = "Block device";
            break;
        case S_IFIFO:
            file_type = "FIFO/pipe";
            break;
        case S_IFLNK:
            file_type = "Symbolic link";
            break;
        case S_IFSOCK:
            file_type = "Socket";
            break;
        default:
            file_type = "Unknown";
            break;
    }
    
    printf("************Information file************\n");
    printf("File type: %s\n", file_type);
    printf("Filename: %s\n", filename);
    printf("Last file modification: %s", ctime(&sb.st_mtime));
    printf("File size: %jd bytes\n",(intmax_t) sb.st_size);

    return 0;
}