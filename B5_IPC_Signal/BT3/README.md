# Answer for EX3
Why do we need to use kill() to send a signal in this program?
The kill() system call ensures communication between the parent and child by sending the desired signal directly to the target process identified by its PID.