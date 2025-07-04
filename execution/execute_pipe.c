/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:29:11 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 13:06:00 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Fork and execute right side of pipe
 * @param shell Shell structure
 * @param tree Pipe tree node
 * @param fd Pipe file descriptors
 * @return Process ID of forked child
 */
static pid_t	right_pipe(t_shell *shell, t_tree *tree, int fd[2])
{
	pid_t	pid;
	int		exit_code;

	signal_heredoc();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_clear(shell, 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal_dfl();
		if (isatty(STDIN_FILENO))
			enable_echoctl();
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute(shell, tree->rhs);
		exit_code = exit_status("exit status", -1);
		ft_clear(shell, 2);
		exit(exit_code);
	}
	return (pid);
}

/**
 * @brief Fork and execute left side of pipe
 * @param shell Shell structure
 * @param tree Pipe tree node
 * @param fd Pipe file descriptors
 * @return Process ID of forked child
 */
static pid_t	left_pipe(t_shell *shell, t_tree *tree, int fd[2])
{
	pid_t	pid;
	int		exit_code;

	signal_heredoc();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		ft_clear(shell, 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal_dfl();
		if (isatty(STDIN_FILENO))
			enable_echoctl();
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(shell, tree->lhs);
		exit_code = exit_status("exit status", -1);
		ft_clear(shell, 2);
		exit(exit_code);
	}
	return (pid);
}

void	execute_pipe(t_shell *shell, t_tree *tree)
{
	int		pipe_fd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status_left;
	int		status_right;

	exit_status("exit status", 0);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		ft_clear(shell, 2);
		return ;
	}
	pid_left = left_pipe(shell, tree, pipe_fd);
	pid_right = right_pipe(shell, tree, pipe_fd);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	waitpid(pid_left, &status_left, 0);
	waitpid(pid_right, &status_right, 0);
	signal_init();
	if (isatty(STDIN_FILENO))
		disable_echoctl();
	if (WIFEXITED(status_right))
		exit_status("exit status", WEXITSTATUS(status_right));
}
