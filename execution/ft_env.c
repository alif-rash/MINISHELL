/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:46:54 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp || !*envp)
	{
		printf("env: No environment variables set.\n");
		return (1);
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
