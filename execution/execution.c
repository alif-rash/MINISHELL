/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:11:44 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/24 10:23:55 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Execute logical AND operation
 * @param shell Shell structure
 * @param tree AND tree node
 */
static void	execute_and(t_shell *shell, t_tree *tree)
{
	ft_dup(shell);
	execute(shell, tree->lhs);
	close_fds(shell);
	if (exit_status("exit status", -1) == 0)
	{
		ft_dup(shell);
		execute(shell, tree->rhs);
		close_fds(shell);
	}
}

void	execute(t_shell *shell, t_tree *tree)
{
	if (!shell->ast || !tree)
		return ;
	if (tree->type == T_LOGICAND)
		execute_and(shell, tree);
	else if (tree->type == T_LOGICOR)
	{
		ft_dup(shell);
		execute(shell, tree->lhs);
		close_fds(shell);
		if (exit_status("exit status", -1) != 0)
		{
			ft_dup(shell);
			execute(shell, tree->rhs);
			close_fds(shell);
		}
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
