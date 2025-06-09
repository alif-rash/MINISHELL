/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:05:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/09 19:33:55 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_str_cmd(char *s1, const char *s2)
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

static int	strcmp_command(t_shell *shell, char *command, char **args)
{
	int	i;

	i = 1;
	if (ft_str_cmd(command, "echo") == 0)
		return (ft_echo(args));
	if (ft_str_cmd(command, "cd") == 0)
		return (ft_cd(args, shell));
	if (ft_str_cmd(command, "pwd") == 0)
		return (ft_pwd());
	if (ft_str_cmd(command, "export") == 0)
		return (ft_export(args, shell, shell->env_list->flag));
	if (ft_str_cmd(command, "unset") == 0)
		return (ft_unset(args, shell));
	if (ft_str_cmd(command, "env") == 0)
		return (ft_env(shell->env_list));
	if (ft_str_cmd(command, "exit") == 0)
		return (ft_exit(args));
	return (5);
}

void	execute_command(t_shell *shell, t_tree *ast)
{
	int		command_return_type;

	if (!shell || !ast)
		return ;
	if (!ast || !ast->args || !ast->args[0])
		return ;
	expand_command(shell, ast);
	command_return_type = strcmp_command(shell, ast->args[0], ast->args);
	if (command_return_type == 0)
		exit_status("exit status", 0);
	// if (command_return_type == 5)
	// 	external_execution(shell, ast);
}
