
# IPC MESSAGE QUEUES

## How to run
```bash
make
./task_worker
./task_dispatcher <priority> <task_description>
```
where: priority is a priority of message, task_description is a data want to send

### Example
Terminal 1:
```bash
./task_worker
```
Terminal 2:
```bash
./task_dispatcher 0 Hello 
```

Terminal 3:
```bash
./task_dispatcher 1 Hi
```