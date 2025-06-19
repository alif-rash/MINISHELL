/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:13:26 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 12:23:25 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		exit_status("exit status", 1);
		close(STDIN_FILENO);
		exit(1);
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
	if (shell->stdin < 0)
		perror("dup stdin");
	shell->stdout = dup(STDOUT_FILENO);
	if (shell->stdout < 0)
		perror("dup stdout");
}

void	close_fds(t_shell *shell)
{
	if (shell->stdin >= 0 && dup2(shell->stdin, STDIN_FILENO) == -1)
		perror("dup2 stdin");
	if (shell->stdout >= 0 && dup2(shell->stdout, STDOUT_FILENO) == -1)
		perror("dup2 stdout");
	if (shell->stdin >= 0)
	{
		close(shell->stdin);
		shell->stdin = -1;
	}
	if (shell->stdout >= 0)
	{
		close(shell->stdout);
		shell->stdout = -1;
	}
}
