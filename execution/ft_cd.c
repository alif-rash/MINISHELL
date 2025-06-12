/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/12 15:49:16 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_cd_args(char **args, t_shell *shell, char **path)
{
	if (!args[1])
	{
		*path = search_in_env(shell, "HOME");
		if (!*path)
		{
			handle_error(shell, args[0], ERROR_GENERIC, NO_HOME);
			return (1);
		}
	}
	else
		*path = args[1];
	return (0);
}

static int	update_pwd_vars(t_shell *shell, char *oldpwd, char *newpwd)
{
	char	*pwd_var;
	char	*oldpwd_var;

	pwd_var = search_in_env(shell, "PWD");
	oldpwd_var = search_in_env(shell, "OLDPWD");
	if (oldpwd_var)
	{
		if (oldpwd)
			update_env(shell, "OLDPWD", oldpwd);
		else
			update_env(shell, "OLDPWD", "");
	}
	if (pwd_var)
	{
		if (newpwd)
			update_env(shell, "PWD", newpwd);
		else
			update_env(shell, "PWD", "");
	}
	free(newpwd);
	free(oldpwd);
	return (0);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;
	char	*new_path;
	char	*curpwd;
	char	*newpwd;

	if (handle_cd_args(args, shell, &path))
		return (1);
	new_path = ft_strtrim(path, "\"");
	curpwd = getcwd(NULL, 0);
	if (!curpwd)
		curpwd = ft_strdup("");
	if (chdir(new_path) == -1)
	{
		handle_error(shell, args[1], ERROR_GENERIC, NO_DIR);
		free(curpwd);
		free(new_path);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		newpwd = ft_strdup("");
	free(new_path);
	return (update_pwd_vars(shell, curpwd, newpwd));
}
