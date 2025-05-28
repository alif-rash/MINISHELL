/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/05/28 07:58:36 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	char	*home;

	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		home = getenv("HOME");
		if (home && chdir(home) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	else if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
