/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:11:44 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/12 09:01:44 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_shell *shell, t_tree *tree)
{
	if (!shell->ast || !tree)
		return ;
	if (tree->type == T_LOGICAND)
	{
		execute(shell, tree->lhs);
		if (exit_status("exit status", -1) == 0)
			execute(shell, tree->rhs);
	}
	else if (tree->type == T_LOGICOR)
	{
		execute(shell, tree->lhs);
		if (exit_status("exit status", -1) != 0)
			execute(shell, tree->rhs);
	}
	else if (tree->type == T_PIPE)
		execute_pipe(shell, tree);
	else if (tree->type >= T_REDIRECT_IN && tree->type <= T_HEREDOC)
		execute_redirections(shell, tree);
	else if (tree->type == T_COMMAND)
		execute_command(shell, tree);
	else if (tree->type == T_BRACKET)
		execute_subshell(shell, tree);
}
