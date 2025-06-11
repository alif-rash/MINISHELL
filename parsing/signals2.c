/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:13:26 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/11 09:23:31 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		exit_status("exit status", 1);
		close(STDIN_FILENO);
	}
}

void	signal_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_and_exitstatus(int status)
{
	char	*msg;
	int		sig;

	if (WIFEXITED(status))
		exit_status("exit status", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT || sig == SIGSEGV || sig == SIGINT)
		{
			if (sig == SIGQUIT)
				write(2, "Quit: 3\n", 8);
			else if (sig == SIGSEGV)
			{
				write(2, "Segmentation fault: ", 20);
				msg = ft_itoa(sig);
				write(2, msg, ft_strlen(msg));
				free(msg);
				write(2, "\n", 1);
			}
			else
				write(2, "\n", 1);
			exit_status("exit status", 128 + sig);
		}
	}
}

void	ft_dup(t_shell *shell)
{
	shell->stdin = dup(STDIN_FILENO);
	if (shell->stdin == -1)
	{
		perror("dup stdin");
		exit(EXIT_FAILURE);
	}
	shell->stdout = dup(STDOUT_FILENO);
	if (shell->stdout == -1)
	{
		perror("dup stdout");
		exit(EXIT_FAILURE);
	}
}

void	close_fds(t_shell *shell)
{
	if (shell->stdin != -1 && dup2(shell->stdin, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (shell->stdout != -1 && dup2(shell->stdout, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	if (shell->stdin != -1)
	{
		close(shell->stdin);
		shell->stdin = -1;
	}
	if (shell->stdout != -1)
	{
		close(shell->stdout);
		shell->stdout = -1;
	}
}
