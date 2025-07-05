/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:16:23 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 11:46:05 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_str_cmd(char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i] && s1[i] + 32 != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	handle_noexec(t_shell *shell, char *exec_path, char *cmd)
{
	char	*argv[3];

	argv[0] = "/bin/sh";
	argv[1] = exec_path;
	argv[2] = NULL;
	execve("/bin/sh", argv, shell->env_array);
	return (handle_error(shell, cmd, ERROR_GENERIC, NOT_FOUND), 127);
}

int	handle_exec_errors(t_shell *shell, char *exec_path, char *cmd, int found)
{
	if (exec_path && access(exec_path, F_OK) == 0)
		return (handle_error(shell, cmd, ERROR_GENERIC, DENIED), 126);
	if (!found && (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')))
		return (handle_error(shell, cmd, ERROR_GENERIC, NO_DIR), 127);
	return (handle_error(shell, cmd, ERROR_GENERIC, NOT_FOUND), 127);
}

char	*trim_brackets(char *str)
{
	char	*trimmed;

	if (ft_strlen(str) == 2)
		return (ft_strdup(""));
	trimmed = ft_substr(str, 1, ft_strlen(str) - 2);
	return (trimmed);
}
