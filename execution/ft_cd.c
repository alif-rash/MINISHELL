/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/30 21:12:52 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_cd_args(char **args, t_shell *shell, char **path)
{
	char	*unquoted_path;

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
			return (handle_error(shell, args[0], ERROR_GENERIC, NO_OLDPWD), 1);
		unquoted_path = ft_strtrim(*path, "\"");
		printf("%s\n", unquoted_path);
		free(unquoted_path);
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

static char	*get_current_pwd(t_shell *shell, char *new_path)
{
	char	*curpwd;
	char	*pwd_from_env;

	curpwd = getcwd(NULL, 0);
	if (!curpwd)
	{
		pwd_from_env = search_in_env(shell, "PWD");
		if (pwd_from_env)
			curpwd = ft_strdup(pwd_from_env);
		else
			curpwd = ft_strdup("");
		if (ft_strcmp(new_path, "..") == 0)
			handle_error(shell, "cd", ERROR_WARNING, CD_GETCWD_WARNING);
	}
	return (curpwd);
}

static char	*construct_new_pwd(char *curpwd, char *new_path)
{
	char	*newpwd;
	char	*unquoted_curpwd;

	if (ft_strcmp(new_path, "..") == 0)
	{
		unquoted_curpwd = ft_strtrim(curpwd, "\"");
		newpwd = ft_strjoin(unquoted_curpwd, "/..");
		free(unquoted_curpwd);
	}
	else if (new_path[0] == '/')
		newpwd = ft_strdup(new_path);
	else
	{
		unquoted_curpwd = ft_strtrim(curpwd, "\"");
		if (ft_strlen(unquoted_curpwd) > 0 && unquoted_curpwd[ft_strlen(unquoted_curpwd) - 1] != '/')
		{
			char *temp = ft_strjoin(unquoted_curpwd, "/");
			newpwd = ft_strjoin(temp, new_path);
			free(temp);
		}
		else
			newpwd = ft_strjoin(unquoted_curpwd, new_path);
		free(unquoted_curpwd);
	}
	return (newpwd);
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
	curpwd = get_current_pwd(shell, new_path);
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
		newpwd = construct_new_pwd(curpwd, new_path);
	free(new_path);
	return (update_pwd_vars(shell, curpwd, newpwd));
}
