/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/15 12:44:53 by raalifa          ###   ########.fr       */
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
	else if (args[1][0] == '-' && args[1][1] == '\0')
	{
		*path = search_in_env(shell, "OLDPWD");
		if (!*path)
		{
			handle_error(shell, args[0], ERROR_GENERIC, NO_OLDPWD);
			return (1);
		}
	}
	else
		*path = args[1];
	return (0);
}

static t_env	*find_env_var(t_shell *shell, const char *name)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

static int	update_pwd_vars(t_shell *shell, char *oldpwd, char *newpwd)
{
	t_env	*pwd_var;
	t_env	*oldpwd_var;

	if (oldpwd)
	{
		oldpwd_var = find_env_var(shell, "OLDPWD");
		if (oldpwd_var)
			update_env(shell, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (newpwd)
	{
		pwd_var = find_env_var(shell, "PWD");
		if (pwd_var)
			update_env(shell, "PWD", newpwd);
		free(newpwd);
	}
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
		handle_error(shell, args[1], ERROR_GENERIC, NO_DIR_CD);
		if (curpwd)
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
