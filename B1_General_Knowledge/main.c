#include "utils.h"

typedef enum cmd
{
    CMD_REVERSE,
    CMD_TRIM,
    CMD_TO_INT,
    CMD_EXIT,
    CMD_UNKNOWN
} cmd_t;
bool running = true;

bool         is_input_ready();
void         handle_input();
static cmd_t string_to_cmd(const char* cmd);

int main()
{
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    if (!init_logging(DEFAULT_LOG_PATH))
    {
        printf("Init logging failed");
        return 0;
    }

    // default level log is info
    // set_level_log(DEBUG);

    log_info("Hello ");
    while (running)
    {
        if (is_input_ready())
        {
            handle_input();
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
    char buf[100];
    int  n = read(STDIN_FILENO, buf, sizeof(buf) - 1);

    if (n > 0)
    {
        buf[n] = '\0';
        if (buf[n - 1] == '\n') buf[n - 1] = '\0';
        log_debug("User entered: %s", buf);

        char* cmd_str = strtok(buf, " ");
        char* arg_str = strtok(NULL, "");

        cmd_t cmd = string_to_cmd(cmd_str);

        switch (cmd)
        {
            case CMD_REVERSE:
            {
                char tmp_buf[50];

                if (!str_reverse(arg_str, tmp_buf))
                {
                    log_warning("Reverse failed for: %s", arg_str);
                    break;
                }

                log_info("Reverse: %s", tmp_buf);
                break;
            }

            case CMD_TRIM:
            {
                char tmp_buf[50];
                if (!str_trim(arg_str, tmp_buf))
                {
                    log_warning("Trim failed for: %s", arg_str);
                    break;
                }

                log_info("Trim: %s", tmp_buf);
                break;
            }

            case CMD_TO_INT:
            {
                int value = 0;

                if (!str_to_int(arg_str, &value))
                {
                    log_warning("Invalid number: %s", arg_str);
                    break;
                }

                log_info("ToInt: %d", value);
                break;
            }

            case CMD_EXIT:
            {
                running = false;
                log_debug("Exit command received");
                break;
            }

            default:
                log_warning("Unknown command: %s", cmd_str);
                break;
        }
    }
}

static cmd_t string_to_cmd(const char* str)
{
    if (str == NULL) return CMD_UNKNOWN;

    if (strcmp(str, "reverse") == 0) return CMD_REVERSE;
    if (strcmp(str, "trim") == 0) return CMD_TRIM;
    if (strcmp(str, "toint") == 0) return CMD_TO_INT;
    if (strcmp(str, "exit") == 0) return CMD_EXIT;

    return CMD_UNKNOWN;
}
