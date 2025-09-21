# Answer for EX2

## Why do we need to use a mutex 
Because all three threads are accessing and modifying the same global variable (counter). Without synchronization, multiple threads may try to read and write counter at the same time. This can lead to a race condition, where the final result depends on the unpredictable timing of thread execution.

Using a pthread_mutex_t ensures that only one thread at a time can update the shared variable. This guarantees that every increment operation is performed correctly, and the final value of counter will be consistent

## How to run
```bash
./main <chose_mode_to_run>
```
where: 
mode_no_mutex: threads are accessing and modifying the same variable
mode_mutex: only one thread at a time can update the shared variable
