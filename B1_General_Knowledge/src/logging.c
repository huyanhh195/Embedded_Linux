#include "logging.h"

log_level_t current_log_level = INFO;

const char *log_level_to_string(log_level_t level)
{
    switch (level)
    {
        case CRITICAL:
            return "CRITICAL";
        case ERROR:
            return "ERROR";
        case WARNING:
            return "WARNING";
        case INFO:
            return "INFO";
        case DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    }
}

const char *log_level_to_color(log_level_t level)
{
    switch (level)
    {
        case CRITICAL:
            return COLOR_MAGENTA;
        case ERROR:
            return COLOR_RED;
        case WARNING:
            return COLOR_YELLOW;
        case INFO:
            return COLOR_WHITE;
        case DEBUG:
            return COLOR_GREEN;
        default:
            return COLOR_WHITE;
    }
}

bool init_logging(const char *file_path)
{
    FILE *fptr = fopen(file_path, "w");
    if (fptr == NULL)
    {
        return false;
    }

    strncpy(log_file_path, file_path, sizeof(log_file_path) - 1);
    log_file_path[sizeof(log_file_path) - 1] = '\0';

    fclose(fptr);

    return true;
}

bool log_message(log_level_t level, const char *fmt, ...)
{
    if (log_file_path[0] == '\0') return false;

    va_list args;

    time_t     now       = time(0);
    struct tm *time_info = localtime(&now);

    char time_stamp[20];
    strftime(time_stamp, sizeof(time_stamp), "%y%m%d-%H:%M:%S", time_info);

    if (level >= current_log_level)
    {
        va_start(args, fmt);
        fprintf(stdout,
                "%s[%s] [%s] ",
                log_level_to_color(level),
                time_stamp,
                log_level_to_string(level));
        vprintf(fmt, args);
        printf("%s\n", COLOR_RESET);
        va_end(args);
    }

    FILE *fptr = fopen(log_file_path, "a");
    if (fptr == NULL)
    {
        perror("[log_message]");
        return false;
    }

    va_start(args, fmt);
    fprintf(fptr, "[%s] [%s] ", time_stamp, log_level_to_string(level));
    vfprintf(fptr, fmt, args);
    fprintf(fptr, "\n");
    va_end(args);

    fclose(fptr);

    return true;
}

bool set_level_log(log_level_t level)
{
    if (level >= DEBUG && level <= CRITICAL)
    {
        current_log_level = level;
        return true;
    }

    return false;
}