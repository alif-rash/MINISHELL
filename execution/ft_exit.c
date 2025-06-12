/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:55 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/12 15:44:42 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args, t_shell *shell)
{
	int	num;

	if (!args[1])
	{
		printf("exit\n");
		exit(exit_status("exit status", 0));
	}
	if (args[1] && args[2])
	{
		printf("exit\n");
		handle_error(shell, NULL, ERROR_GENERIC, TOO_MANY_ARGS);
		return (1);
	}
	if (args[1])
	{
		if (!ft_isnumeric(args[1]))
			handle_error(shell, args[1], ERROR_NUMERIC, NUM_REQUIRED);
	}
	num = ft_atoi(args[1]);
	printf("exit\n");
	ft_clear(shell, 2);
	exit((unsigned char)num);
	return (1);
}
