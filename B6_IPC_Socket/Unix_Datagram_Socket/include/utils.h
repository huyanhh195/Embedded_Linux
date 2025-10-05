#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define LOG_INFO(fmt, ...)                           \
    do                                               \
    {                                                \
        printf("[INFO] - " fmt "\n", ##__VA_ARGS__); \
    } while (0);

#define LOG_ERROR(fmt, ...)                           \
    do                                                \
    {                                                 \
        printf("[ERROR] - " fmt "\n", ##__VA_ARGS__); \
    } while (0);

#define msleep(times) usleep(times * 1000)

static void signal_handler();
void       *handle_send_thread(void *arg);
void       *handle_recv_thread(void *arg);

static int flag_running = 1;
static int cnt_signal   = 0;