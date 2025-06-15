#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iostream>
#include <csignal>

using namespace std;

static const string LOG_PATH = "logs/log.txt";
extern ofstream logFile; 

enum log_level_t {
    DEBUG, 
    INFO, 
    WARNING, 
    ERROR, 
    CRITICAL 
};

class Logger {
private:

    // Fuction to create log file
    void create_log_file(const string& file_name);

    // Chane log level to string
    string log_level_to_string(log_level_t level);
    
public:

    Logger(const string& file_name = LOG_PATH);
    ~Logger();

    // Fuction to log message
    void log_message(log_level_t level, const std::string& message);
};
