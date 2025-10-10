#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#include "logging.h"

#define ON               1
#define OFF              0
#define INET_ADDRSTRLEN  16
#define MAX_PEER         50
#define TIME_SLEEP       100000
#define DEFAULT_LOG_PATH "./logging/log.txt"

typedef enum
{
    CMD_HELP,
    CMD_MY_IP,
    CMD_MY_PORT,
    CMD_CONNECT,
    CMD_LIST,
    CMD_TERMINATE_IP,
    CMD_SEND_IP_MSG,
    CMD_EXIT,
    CMD_UNKNOWN
} cmd_t;

typedef struct
{
    struct sockaddr_in addr;
    bool               active;
    int                socket_fd;
    int                port;
    int                id;
    pthread_t          thread_recv;
    char               ip[INET_ADDRSTRLEN];
} peer_info_t;  // bytes

typedef struct
{
    struct sockaddr_in addr;
    int                socket_fd;
    int                peer_count;
    peer_info_t        peer_list[MAX_PEER];
} socket_info_t;  // bytes

// ==================== Display & Information Utilities ====================

/**
 * @brief Show command usage instructions.
 */
void show_help();

/**
 * @brief Display the local IP address.
 */
char* get_ip();

/**
 * @brief Display the local port number.
 */
void show_port();

/**
 * @brief Print all current active peer connections.
 */
void show_list_connection();

// ==================== Input & Command Processing ====================

/**
 * @brief Check if there is user input ready to be read.
 * @return true if input is available, false otherwise.
 */
bool is_input_ready();

/**
 * @brief Handle a command entered by the user.
 */
void handle_input();

/**
 * @brief Convert input string to command enum type.
 * @return Corresponding command type.
 */
cmd_t string_to_cmd();

// ==================== Socket Initialization & Threads ====================

/**
 * @brief Validate a port string (check if numeric and within valid range).
 * @param str_port Port number in string format.
 * @return true if valid, false otherwise.
 */
bool check_valid_port(const char* str_port);

/**
 * @brief Initialize a TCP socket and start listening on the given port.
 * @param sock Pointer to socket information structure.
 * @param port Port number to bind.
 * @return true if successfully initialized, false otherwise.
 */
bool init_socket(socket_info_t* sock, int port);

/**
 * @brief Remove and clean up all inactive peers.
 * @param sock Pointer to socket info structure.
 */
void cleanup_inactive_peers(socket_info_t* sock);

/**
 * @brief Thread to continuously accept new incoming connections.
 * @param arg Pointer to socket_info_t.
 * @return NULL
 */
void* handle_connect_thread(void* arg);

/**
 * @brief Thread to handle receiving messages from connected peers.
 * @param arg Pointer to socket_info_t or connection context.
 * @return NULL
 */
void* handle_recv_msg_thread(void* arg);

// ==================== Command Handlers ====================

/**
 * @brief Connect to another peer using IP and port.
 * @param str Command string containing "ip port".
 */
void handle_cmd_connect(char* str);

/**
 * @brief Terminate a connection with a specific peer by ID.
 * @param str Command string containing peer ID.
 */
void handle_cmd_terminate(char* str);

/**
 * @brief Send a message to a specific peer by ID.
 * @param str Command string containing "id message".
 */
void handle_cmd_send(char* str);

// ==================== Utility Functions ====================

/**
 * @brief Sleep for a specified time in milliseconds.
 * @param times Time to sleep in milliseconds.
 */
void msleep(int times);

/**
 * @brief handle SIGINT signal
 * @param sig Signal number
 */
void signal_handler(int sig);
