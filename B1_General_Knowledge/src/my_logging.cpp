#include "my_logging.hpp"
ofstream logFile; 

Logger::Logger(const string& file_name){
    create_log_file(file_name);
}

Logger::~Logger(){
    logFile.close();
}

void Logger::create_log_file(const string& file_name){
    logFile.open(file_name, ios::app);
    if (logFile.is_open()) {
        cout << "Created log file with name " << file_name << endl;
    }
    else {
        cout << "Error creating log file" << endl;
    }
}

void Logger::log_message(log_level_t level, const string& message){
    // Get current time 
    time_t now = time(0);
    tm* timeinfo = localtime(&now);

    // Format the time
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),"%Y-%m-%d %H:%M:%S", timeinfo);

    // Construct the log entry string
    ostringstream logEntry;
    logEntry << "[" << timestamp << "] [" << log_level_to_string(level) << "]" << message << endl;

    if(logFile.is_open()){
        logFile << logEntry.str();
        logFile.flush();
    }
    else{
        cout << "Error openning log file" << endl;
    }
}


string Logger::log_level_to_string(log_level_t level){
    string level_string;

    switch (level){
        case DEBUG:
            level_string = "DEBUG";
            break;
        case INFO:
            level_string = "INFO";
            break;
        case WARNING:
            level_string = "WARNING";
            break;
        case ERROR:
            level_string = "ERROR";
            break;
        case CRITICAL:
            level_string = "CRITICAL";
            break;
        default:
            level_string = "UNKNOWN";
            break;
    }

    return level_string;
}
