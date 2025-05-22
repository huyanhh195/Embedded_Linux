#include "main.hpp"

int main(){
    create_log_file();
    // log_message(DEBUG, "test");
    signal(SIGINT, singal_handler);

    int cnt = 0;
    while(program_running){

        // log
        cout << "Counting: " << cnt << endl;
        log_message(INFO, " " + to_string(cnt));
        
        if (cnt >= NUMBER_COUNTS){
            break;
        }

        // Increase the counter
        cnt += 1;
        
        sleep(1);
    }

    cout << "Done" << endl;
    log_message(WARNING, " Done");
    log_message(WARNING, " **********************");
    logFile.close();

    return 0;
}   

void singal_handler(int signal){
    program_running = false;
    log_message(WARNING, " Exiting with signal");
}