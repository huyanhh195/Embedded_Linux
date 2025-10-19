#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define MAX_NUM 10

typedef struct
{
    int   id;
    float price;
    char  name[32];
} MyProduct;