#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

#include "logging.h"

#define DEFAULT_LOG_PATH "./logs/logging.txt"
#define TIME_SLEEP       100000