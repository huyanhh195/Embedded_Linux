#pragma once

#include <csignal>
#include <unistd.h>
#include "my_logging.hpp"

#define NUMBER_COUNTS 10

void signal_handler(int signal);

