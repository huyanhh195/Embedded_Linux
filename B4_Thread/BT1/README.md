# Answer for EX1
## pthread_create()
 - This function is used to create a new thread. It starts a new thread in the calling process.
 - Prototype:
```bash
int pthread_create(pthread_t *restrict thread,
                   const pthread_attr_t *restrict attr,
                   typeof(void *(void *)) *start_routine,
                   void *restrict arg);
```
where:
    thread : Pointer to a pthread_t variable where the system can store the ID of the new thread.
    attr : Pointer to a thread attributes object that defines thread properties. Use NULL for default attributes.
    routine: Pointer to the function that the thread will execute. It must return void* and accept a void* argument.
    arg: A single argument passed to the thread function. Use NULL if no argument is needed. We can pass a struct or pointer to pass multiple values.
    
Return value:
    0 on success.
    On error, it returns an error number and the contents of thread are undefined

---

## pthread_join()
 - This function is used to wait for the thread specified to finish. If that thread has already terminated, then pthread_join() returns immediately.
 - Prototype:
```bash
int pthread_join(pthread_t thread, 
                 void **retval);
```
where:
    thread: The ID of the thread you want to wait for. This is the thread that will be joined.
    retval: A pointer to a location where the exit status of the thread will be stored. This is optional and can be set to NULL if you do not need the return value of the thread.

Return value:
    0 on success. On error, it returns an error number.

---

## When thread terminate
1. The thread function returns
If the function passed to pthread_create() finishes executing and executes a return, the thread ends.

2. The thread calls pthread_exit()
A thread can explicitly call pthread_exit(void *retval). This immediately terminates the calling thread and makes retval available to pthread_join().

3. Another thread calls pthread_cancel() on it
A different thread can request cancellation of a thread using pthread_cancel(thread_id).
The target thread may or may not respond immediately, depending on its cancellation settings.

4. The entire process ends
If the main thread (or any thread) calls exit() or the process is killed, all threads terminate together, regardless of their state.
Similarly, if the main thread finishes without calling pthread_exit(), the process ends and all threads are terminated.