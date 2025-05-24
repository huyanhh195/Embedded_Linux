#pragma once

#include <csignal>
#include <unistd.h>
#include "my_logging.hpp"
// #include "my_string.hpp"

void singal_handler(int signal);

int program_running = true;
int NUMBER_COUNTS = 10;

// MAIN_h