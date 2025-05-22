#pragma once

/* ********************************************************************************** */
//
// logging Level: DEBUG, INFO, ERROR and CRITICAL
//
/* ********************************************************************************** */

// include libs
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <csignal>

using namespace std;

// enum log leves
enum log_level_t {
    DEBUG, 
    INFO, 
    WARNING, 
    ERROR, 
    CRITICAL 
};

static const string LOG_PATH = "logs/log.txt";

// Create a log file
void create_log_file(const string& file_name = LOG_PATH);

// Log a message
void log_message(log_level_t level, const std::string& message);

// chane log level to string
string log_level_to_string(log_level_t level);

extern ofstream logFile; 

// MU_LOGGING_H