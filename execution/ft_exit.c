/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:47:55 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/11 11:24:25 by hparveen         ###   ########.fr       */
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
	ft_clear(shell, 2);
	exit((unsigned char)num);
	return (1);
}
