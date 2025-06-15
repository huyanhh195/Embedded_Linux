#include "utils.hpp"

int flag_run = true;

int main(){
    int cnt = 0;
    Logger logger;       

    signal(SIGINT, signal_handler);

    while(flag_run){
        
        cout << "Counting: " << cnt << endl;
        logger.log_message(INFO, " Counting: " + to_string(cnt));
        
        if (cnt >= NUMBER_COUNTS){
            break;
        }

        cnt += 1;
        
        sleep(1);
    }

    // check if receive SIGINT signal
    if (!flag_run){
        cout << "Exiting with signal" << endl;
        logger.log_message(WARNING, " Exiting with signal");
    }

    cout << "Done" << endl;
    logger.log_message(WARNING, " Done");
    logger.log_message(WARNING, " **********************");
    
    return 0;
}   

void signal_handler(int signal){
    flag_run = false;
}