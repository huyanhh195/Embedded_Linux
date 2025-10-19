#include "utils.h"

int main()
{
    const char*  name = "/my_shm";
    const size_t SIZE = 4096;
    int          shm_fd;
    void*        ptr = NULL;

    // Open shared memory object
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        perror("Failed to open shared memory object");
        return 1;
    }

    // Map shared memory object to process's address space
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Failed to map shared memory object");
        return 1;
    }

    // Read data from shared memory
    MyProduct* list_data = (MyProduct*)ptr;
    for (int i = 0; i < MAX_NUM; i++)
    {
        printf("ID: %d, Name: %s, Price: %.2f\n",
               list_data[i].id,
               list_data[i].name,
               list_data[i].price);
    }

    if (shm_unlink(name) == -1)
    {
        perror("Failed to unlink shared memory object");
        return 1;
    }

    close(shm_fd);
}