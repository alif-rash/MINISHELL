#include "minishell.h"

void handle_heredoc(int signal)
{
    if(signal == SIGINT)
    {
        exit_status("exit status", 1);
        close(STDIN_FILENO);
    }
}
