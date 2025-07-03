/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:05:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/23 13:28:47 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	strcmp_command(t_shell *shell, char *command, char **args)
{
	if (ft_str_cmd(command, "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(command, "cd") == 0)
		return (ft_cd(args, shell));
	if (ft_str_cmd(command, "pwd") == 0)
		return (ft_pwd(shell));
	if (ft_strcmp(command, "export") == 0)
		return (ft_export(args, shell));
	if (ft_strcmp(command, "unset") == 0)
		return (ft_unset(args, shell));
	if (ft_str_cmd(command, "env") == 0)
		return (ft_env(shell->env_list));
	if (ft_strcmp(command, "exit") == 0)
		return (ft_exit(args, shell));
	return (5);
}

static void	copy_non_empty_args(char **src, char **dst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i][0] != '\0')
			dst[j++] = ft_strdup(src[i]);
		i++;
	}
	dst[j] = NULL;
}

static int	count_non_empty_args(char **args)
{
	int	count;
	int	i;

	if (!args)
		return (0);
	count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	filter_empty_args(t_tree *tree)
{
	char	**new_args;
	int		count;

	if (!tree || !tree->args)
		return ;
	count = count_non_empty_args(tree->args);
	if (count == 0)
	{
		ft_free_array(tree->args);
		tree->args = NULL;
		return ;
	}
	new_args = malloc(sizeof(char *) * (count + 1));
	if (!new_args)
		return ;
	copy_non_empty_args(tree->args, new_args);
	ft_free_array(tree->args);
	tree->args = new_args;
}

void	execute_command(t_shell *shell, t_tree *ast)
{
	int	command_return_type;

	if (!shell || !ast)
		return ;
	if (!ast || !ast->args || !ast->args[0])
		return ;
	if (expand_command(shell, ast))
	{
		filter_empty_args(ast);
		if (!ast->args || !ast->args[0])
			return ;
	}
	command_return_type = strcmp_command(shell, ast->args[0], ast->args);
	if (command_return_type == 0)
		exit_status("exit status", 0);
	if (command_return_type == 5)
		external_execution(shell, ast);
}
