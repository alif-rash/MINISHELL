/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:55 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/30 21:13:28 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_non_numeric_arg(char *arg, t_shell *shell)
{
	printf("exit\n");
	ft_clear(shell, 2);
	handle_error(shell, arg, ERROR_NUMERIC, NUM_REQUIRED);
	exit(exit_status("exit status", 255));
}

int	ft_exit(char **args, t_shell *shell)
{
	int	num;

	if (!args[1])
	{
		printf("exit\n");
		ft_clear(shell, 2);
		exit(exit_status("exit status", 0));
	}
	if (args[1])
	{
		if (!ft_isnumeric(args[1]))
			exit_non_numeric_arg(args[1], shell);
	}
	if (args[1] && args[2])
	{
		printf("exit\n");
		return (handle_error(shell, NULL, ERROR_GENERIC, TOO_MANY_ARGS), 1);
	}
	num = ft_atoi(args[1]);
	printf("exit\n");
	ft_clear(shell, 2);
	return (exit((unsigned char)num), 1);
}
