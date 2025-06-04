/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:55 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/04 15:13:35 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args)
{
	int	num;

	if (!args[1])
	{
		printf("exit\n");
		exit(exit_status("exit status", 0));
	}
	if (args[1] && args[2])
	{
		ft_perror("exit", "too many arguments");
		return (1);
	}
	if (args[1])
	{
		if (!ft_isnumeric(args[1]))
		{
			ft_perror("exit", "numeric argument required");
			exit(255);
		}
	}
	num = ft_atoi(args[1]);
	printf("exit\n");
	exit((unsigned char)num);
	return (1);
}
