/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:05:03 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_command(t_shell *shell, t_tree *ast)
{
	char *cmd;

	if (!shell || !ast)
		return;
	if (!ast || !ast->args || !ast->args[0])
        return;
    if (ast->type == T_COMMAND)
    {
		cmd = ast->args[0];
        if (ft_strcmp(ast->args[0], "echo") == 0)
            ft_echo(ast->args);
		else if (ft_strcmp(ast->args[0], "cd") == 0)
			ft_cd(shell, ast->args);
		else if (ft_strcmp(cmd, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(cmd, "export") == 0)
			ft_export(shell, ast->args);
		else if (ft_strcmp(cmd, "unset") == 0)
			ft_unset(shell, ast->args);
		else if (ft_strcmp(cmd, "env") == 0)
			ft_env(shell->env_list);
		else if (ft_strcmp(cmd, "exit") == 0)
			ft_exit(ast->args);
    }
    else if (ast->type == T_PIPE)
    {
        
    }
    else if (ast->type == T_REDIRECT_IN || ast->type == T_REDIRECT_OUT ||
             ast->type == T_APPEND || ast->type == T_HEREDOC)
    {
		
    }
}