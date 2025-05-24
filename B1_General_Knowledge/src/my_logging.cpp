#include "my_logging.hpp"
ofstream logFile; 

void create_log_file(const string& file_name){

    logFile.open(file_name, ios::app);
    // Create the file
    if (logFile.is_open()) {
        // logFile.close();
        cout << "Created log file with name " << file_name << endl;
    }
    else {
        cout << "Error creating log file" << endl;
    }
}

void log_message(log_level_t level, const string& message){
    //get current time 
    time_t now = time(0);
    tm* timeinfo = localtime(&now);

    // format the time
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp),"%Y-%m-%d %H:%M:%S", timeinfo);

    ostringstream logEntry;
    logEntry << "[" << timestamp << "] [" << log_level_to_string(level) << "]" << message << endl;

    // output to console
    // cout << logEntry.str();

    // outtput to log file
    // logFile.open(ios::app);
    if(logFile.is_open()){
        logFile << logEntry.str();
        logFile.flush();
    }
    else{
        cout << "Error openning log file" << endl;
    }
}


string log_level_to_string(log_level_t level){
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
