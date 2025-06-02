/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:55 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
	{
		if (args[2])
		{
			fprintf(stderr, "exit: too many arguments\n");
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	printf("exit\n");
	exit(exit_code);
}
