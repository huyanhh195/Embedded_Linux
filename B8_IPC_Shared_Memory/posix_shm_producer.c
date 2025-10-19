#include "utils.h"

int main()
{
    const char*  name = "/my_shm";
    const size_t SIZE = 4096;
    int          shm_fd;
    void*        ptr = NULL;

    // Create shared memory object
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == 1)
    {
        perror("Failed to create shared memory object");
        return 1;
    }

    // Set size of shared memory object
    if (ftruncate(shm_fd, SIZE) == -1)
    {
        perror("Failed to set size of shared memory object");
        return 1;
    }

    // Map shared memory object to process's address space
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("Failed to map shared memory object");
        return 1;
    }

    // Write data to shared memory
    MyProduct* list_data = (MyProduct*)ptr;

    for (int i = 0; i < MAX_NUM; i++)
    {
        int idx = i + 1;

        // Format: Item 1, Item 2,...
        char name_buffer[32];
        snprintf(name_buffer, sizeof(name_buffer), "Item %d", idx);

        list_data[i].id    = idx;
        list_data[i].price = idx * 100.0f;
        strncpy(list_data[i].name, name_buffer, sizeof(list_data[i].name) - 1);
        list_data[i].name[sizeof(list_data[i].name) - 1] = '\0';
    }

    memcpy(ptr, list_data, sizeof(MyProduct) * MAX_NUM);

    return 0;
}