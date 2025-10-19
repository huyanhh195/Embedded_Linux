
# Shared Memory

## Overview
There are two ways to create shared memory:
 - using the shm API (System V)
 - using the mmap API (POSIX)

## Implementation V Shared Memory
1. Create key.
2. Allocate shared memory segment.
3. Map/umap shared memory segment.
4. Free shared memory segment.

## Implementation POSIX Shared Memory
1. Create shared memory object
2. Set size for shared memory object
3. Map/unmap shared memory object
4. Frees the shared memory object

## How to run
```bash
make
./posix_shm_producer
./posix_shm_consumer
```
where: posix_shm_producer: write data to shared memory, posix_shm_consumer receive data from shared memory


