/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/04 13:08:02 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_cd_args(char **args, t_shell *shell, char **path)
{
	if (args[1] && args[2])
	{
		ft_perror("cd", "too many arguments");
		return (1);
	}
	if (!args[1])
	{
		*path = search_in_env(shell, "HOME");
		if (!*path)
		{
			ft_perror("cd", "HOME not set");
			return (1);
		}
	}
	else
		*path = args[1];
	return (0);
}

static int	update_pwd_vars(t_shell *shell, char *oldpwd, char *newpwd)
{
	if (newpwd)
	{
		update_env(shell, "OLDPWD", oldpwd);
		update_env(shell, "PWD", newpwd);
	}
	free(newpwd);
	free(oldpwd);
	return (0);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*new_path;
	char	*oldpwd;
	char	*newpwd;

	if (handle_cd_args(args, shell, &path))
		return (1);
	new_path = ft_strtrim(path, "\"");
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_perror("cd", strerror(errno));
		return (1);
	}
	if (chdir(new_path) == -1)
	{
		ft_perror("cd", strerror(errno)); 
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		ft_perror("cd", "getcwd failed");
	free(new_path);
	return (update_pwd_vars(shell, oldpwd, newpwd));
}
