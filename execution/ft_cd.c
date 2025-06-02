/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(char *args, t_env *env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (!args || !*args)
	{
		path = ft_getenv("HOME", env);
		if (!path)
			perror("cd: HOME not set");
	}
	path = args;
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (newpwd && oldpwd)
	{
		update_env("OLDPWD", oldpwd, env);
		update_env("PWD", newpwd, env);
	}
	free(newpwd);
	free(oldpwd);
	return (0);
}
