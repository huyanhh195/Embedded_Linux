#ifndef _LOGGING_H_
#define _LOGGING_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_WHITE   "\x1b[37m"

static char log_file_path[100] = {0};
typedef enum log_level_t
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
} log_level_t;

bool               init_logging(const char *file_path);
bool               log_message(log_level_t level, const char *fmt, ...);
static const char *log_level_to_string(log_level_t level);
static const char *log_level_to_color(log_level_t level);
bool               set_level_log(log_level_t level);

#define log_debug(fmt, ...)    log_message(DEBUG, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)     log_message(INFO, fmt, ##__VA_ARGS__)
#define log_warning(fmt, ...)  log_message(WARNING, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)    log_message(ERROR, fmt, ##__VA_ARGS__)
#define log_critical(fmt, ...) log_message(CRITICAL, fmt, ##__VA_ARGS__)

#endif