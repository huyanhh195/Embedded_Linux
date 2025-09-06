#include "utils.h"

bool is_input_ready();
void handle_input();

bool running = true;

int main()
{
    static int data = 0;

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    if (!init_logging(DEFAULT_LOG_PATH))
    {
        printf("Init logging failed");
        return 0;
    }

    // default level log is info
    // set_level_log(DEBUG);

    while (running)
    {
        if (is_input_ready())
        {
            handle_input();
        }

        log_debug("Data: %d", data);

        data++;
        if (data % 100 == 0)
        {
            log_warning("Data is: %d", data);
        }

        usleep(TIME_SLEEP);
    }

    return 1;
}

bool is_input_ready()
{
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    struct timeval tv = {0, 0};
    int ret           = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0;

    return ret;
}

void handle_input()
{
    char cmd[32];
    int  n = read(STDIN_FILENO, cmd, sizeof(cmd) - 1);

    if (n > 0)
    {
        cmd[n] = '\0';
        if (cmd[n - 1] == '\n') cmd[n - 1] = '\0';
        log_info("User entered: %s", cmd);
        if (!strcmp(cmd, "exit"))
        {
            running = false;
        }
    }
}
