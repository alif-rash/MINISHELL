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

/**
 * @brief Handle cd command arguments and determine target path
 * @param args Command arguments
 * @param shell Shell structure
 * @param path Pointer to store target path
 * @return 0 on success, 1 on error
 */
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

/**
 * @brief Get current working directory with fallback to PWD
 * @param shell Shell structure
 * @param new_path Target path for error handling
 * @return Current working directory string
 */
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

/**
 * @brief Handle relative path construction
 * @param curpwd Current working directory
 * @param new_path Target path
 * @return New PWD path for relative directory
 */
static char	*handle_relative_path(char *curpwd, char *new_path)
{
	char	*newpwd;
	char	*unquoted_curpwd;
	char	*temp;

	unquoted_curpwd = ft_strtrim(curpwd, "\"");
	if (ft_strlen(unquoted_curpwd) > 0
		&& unquoted_curpwd[ft_strlen(unquoted_curpwd) - 1] != '/')
	{
		temp = ft_strjoin(unquoted_curpwd, "/");
		newpwd = ft_strjoin(temp, new_path);
		free(temp);
	}
	else
		newpwd = ft_strjoin(unquoted_curpwd, new_path);
	free(unquoted_curpwd);
	return (newpwd);
}

/**
 * @brief Construct new PWD path based on current directory and target
 * @param curpwd Current working directory
 * @param new_path Target path
 * @return Constructed new PWD path
 */
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
		newpwd = handle_relative_path(curpwd, new_path);
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
