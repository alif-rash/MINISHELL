/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:43:57 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/18 08:00:49 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(t_shell *shell)
{
	char	*cwd;
	char	*pwd_from_env;
	char	*unquoted_pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
	pwd_from_env = search_in_env(shell, "PWD");
	if (pwd_from_env)
	{
		unquoted_pwd = ft_strtrim(pwd_from_env, "\"");
		printf("%s\n", unquoted_pwd);
		free(unquoted_pwd);
		return (0);
	}
	handle_error(NULL, "pwd: error retrieving current directory",
		ERROR_PERROR, IGNORE);
	return (1);
}
