#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

typedef struct file_stat
{
    const char *file_path;
    struct stat sb;
} file_stat_t;

void        print_stat(file_stat_t *stat_buf);
const char *file_type_string(mode_t mode);
const char *print_time(time_t time, char *buf, size_t bufsize);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file_stat_t stat_buf;
    stat_buf.file_path = argv[1];

    if (lstat(stat_buf.file_path, &stat_buf.sb))
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }

    print_stat(&stat_buf);
}

void print_stat(file_stat_t *stat_buf)
{
    printf("File path: %s\n", stat_buf->file_path);
    printf("File Type: %s", file_type_string(stat_buf->sb.st_mode));

    printf("\nSize: %ld bytes\n", stat_buf->sb.st_size);

    char buf[20];
    printf("Last Modified: %s\n",
           print_time(stat_buf->sb.st_mtime, buf, sizeof(buf)));
}

const char *file_type_string(mode_t mode)
{
    if (S_ISREG(mode)) return "regular file";
    if (S_ISDIR(mode)) return "directory";
    if (S_ISCHR(mode)) return "character device";
    if (S_ISBLK(mode)) return "block device";
    if (S_ISFIFO(mode)) return "FIFO/pipe";
    if (S_ISLNK(mode)) return "symlink";
    if (S_ISSOCK(mode)) return "socket";
    return "unknown";
}

const char *print_time(time_t time, char *buf, size_t buf_size)
{
    struct tm *mtime = localtime(&time);
    strftime(buf, buf_size, "%d-%m-%Y %H:%M:%S", mtime);
    return buf;
}
