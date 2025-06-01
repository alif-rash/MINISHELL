#include "minishell.h"

static int fork_heredoc(t_shell *shell, pid_t *pid, int fd[2], char *delimiter)
{
    *pid = fork();
    if(*pid == -1)
    {
        close(fd[1]);
        close(fd[0]);
       return(1); 
    }
    if(*pid == 0)
    {
        signal(SIGINT, handle_heredoc);
        signal(SIGQUIT, SIG_IGN);
        
    }
}

static int handle_one_heredoc(t_shell *shell, char *delimiter, t_token *current)
{
    pid_t pid;
    int status;
    int pipe_heredoc[2];

    if(pipe(pipe_heredoc) == -1)
        return(1);
    signal_heredoc();
    if(fork_heredoc(shell, &pid, pipe_heredoc, delimiter))
        return(1);
    waitpid(pid, &status, 0);
    signal_init();
    if(WIFEXITED(status) && WEXITSTATUS(status) == 1)
    {
        our_static("exit status", 1);
        close(current->fd);
        return(0);
    }
    close(pipe_heredoc[1]);
    return(pipe_heredoc[0]);
}

void heredoc(t_shell *shell, t_token *tokens)
{
    t_token *current;

    current = tokens;
    while(current)
    {
        if(current->type == T_HEREDOC && current->next && current->next->type == T_DELIMITER)
        {
            current->fd = handle_one_heredoc(shell, current->next->value, current);
        }
    }
}
