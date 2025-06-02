/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 10:56:11 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_status(char *str, int status)
{
	static int	exit_status;

	if (ft_strcmp(str, "exit status") == 0)
	{
		if (status != -1)
			exit_status = status;
		return (exit_status);
	}
	return (0);
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status("exit status", 1);
	}
}

void	signal_init(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	exit_function(t_shell *shell)
{
	(void)shell;
	write(2, "exit\n", 5);
	exit(1);
}
