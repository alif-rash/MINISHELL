/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:12:16 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/24 08:12:56 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Main heredoc reading loop
 * @param end Delimiter to stop reading
 * @param write_end Write end of pipe
 * @param delimiter Original delimiter string
 */
static void	loop(char *end, int write_end, char *delimiter)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		if (g_heredoc_sigint)
			break ;
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			if (!ft_strncmp(line, end, ft_strlen(delimiter) + 1))
			{
				free(line);
				line = NULL;
				break ;
			}
		}
		new_line = ft_strjoin(line, "\n");
		write(write_end, new_line, ft_strlen(new_line));
		free(new_line);
		new_line = NULL;
		free(line);
	}
}

/**
 * @brief Read heredoc input from stdin and write to pipe
 * @param delimiter Heredoc delimiter
 * @param write_end Write end of pipe
 * @param shell Shell structure
 * @param read_end Read end of pipe
 */
static void	read_from_stdin(char *delimiter, int write_end, t_shell *shell,
		int read_end)
{
	char	*limiter;
	char	*end;
	int		len;

	limiter = NULL;
	end = delimiter;
	len = ft_strlen(delimiter);
	if (delimiter[0] == '\'' || delimiter[0] == '"')
	{
		limiter = ft_substr(delimiter, 1, len - 2);
		if (!limiter)
			limiter = ft_strdup("");
	}
	end = delimiter;
	if (limiter)
		end = limiter;
	loop(end, write_end, delimiter);
	close(write_end);
	if (g_heredoc_sigint)
	{
		close(read_end);
		ft_clear(shell, 2);
		exit(1);
	}
}

/**
 * @brief Fork process for heredoc handling
 * @param shell Shell structure
 * @param pid Pointer to store process ID
 * @param fd Pipe file descriptors
 * @param delimiter Heredoc delimiter
 * @return 0 on success, 1 on error
 */
static int	fork_heredoc(t_shell *shell, pid_t *pid, int fd[2], char *delimiter)
{
	*pid = fork();
	if (*pid == -1)
	{
		close(fd[1]);
		close(fd[0]);
		return (1);
	}
	if (*pid == 0)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
		read_from_stdin(delimiter, fd[1], shell, fd[0]);
		close(fd[0]);
		ft_clear(shell, 2);
		exit(0);
	}
	return (0);
}

/**
 * @brief Handle single heredoc operation
 * @param shell Shell structure
 * @param delimiter Heredoc delimiter
 * @param current Current token
 * @return File descriptor or error code
 */
static int	handle_one_heredoc(t_shell *shell, char *delimiter,
		t_token *current)
{
	pid_t	pid;
	int		status;
	int		pipe_heredoc[2];

	if (pipe(pipe_heredoc) == -1)
		return (1);
	signal_heredoc();
	if (fork_heredoc(shell, &pid, pipe_heredoc, delimiter))
		return (1);
	waitpid(pid, &status, 0);
	signal_init();
	if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
	{
		exit_status("exit status", 1);
		shell->heredoc_failed = 1;
		close(pipe_heredoc[0]);
		close(pipe_heredoc[1]);
		current->fd = -1;
		return (-3);
	}
	close(pipe_heredoc[1]);
	return (pipe_heredoc[0]);
}

void	heredoc(t_shell *shell, t_token *tokens)
{
	t_token	*current;
	int		heredoc_interrupted;

	current = tokens;
	heredoc_interrupted = 0;
	while (current)
	{
		if (current->type == T_HEREDOC && current->next
			&& current->next->type == T_DELIMITER)
		{
			current->fd = handle_one_heredoc(shell, current->next->value,
					current);
		}
		if (current->fd == -3)
		{
			heredoc_interrupted = 1;
			break ;
		}
		current = current->next;
	}
	if (heredoc_interrupted)
		shell->heredoc_failed = 1;
}
