/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:49:04 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/27 10:54:10 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_check_brackets(t_token *current)
{
	if (!current->next)
		return (0);
	if (current->next->type == T_BRACKET)
		return (ERR_DOUBLEBRACKET);
	if (current->next->type == T_COMMAND || current->next->type == T_ARGUMENT)
		return (ERR_INVALIDSUBSHELL);
	return (0);
}

int	syntax_check_redirections(t_token *current)
{
	if (!current->next)
		return (ERR_REDIR_SYNTAX);
	if (current->type == T_HEREDOC && current->next->type != T_DELIMITER)
		return (ERR_REDIR_SYNTAX);
	if (current->type != T_HEREDOC && current->next->type != T_FILENAME)
		return (ERR_REDIR_SYNTAX);
	return (0);
}

int	syntax_check_operators(t_token *current, int index)
{
	if (!current->next || current->next->type == T_PIPE
		|| current->next->type == T_LOGICAND
		|| current->next->type == T_LOGICOR)
		return (ERR_OP_SYNTAX);
	if (index == 0)
		return (ERR_OP_START);
	return (0);
}

int	check_syntax(t_shell *shell)
{
	int		error_code;
	int		index;
	t_token	*current;

	index = 0;
	error_code = 0;
	current = shell->token_list;
	while (current)
	{
		if (current->type == T_PIPE || current->type == T_LOGICAND
			|| current->type == T_LOGICOR)
			error_code = syntax_check_operators(current, index);
		if (current->type >= T_REDIRECT_IN && current->type <= T_HEREDOC)
			error_code = syntax_check_redirections(current);
		if (current->type == T_BRACKET)
			error_code = syntax_check_brackets(current);
		if (print_error(shell, error_code, current))
			return (1);
		current = current->next;
		index++;
	}
	return (error_code);
}
