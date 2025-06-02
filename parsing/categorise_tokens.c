/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorise_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:23:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*tokens_after_redirection(t_shell *shell, t_token *list,
		int *is_command)
{
	int	previous_type;

	previous_type = list->type;
	if (!list->next)
		return (handle_error(shell, "new line", ERROR_SYNTAX, '\0'), NULL);
	if (list->next && (list->next->type >= T_REDIRECT_IN
			&& list->next->type <= T_HEREDOC))
		return (handle_error(shell, "new line", ERROR_SYNTAX, '\0'), NULL);
	list = list->next;
	if (list && list->type == T_WORD)
	{
		list->type = T_FILENAME;
		if (previous_type == T_HEREDOC)
			list->type = T_DELIMITER;
	}
	if (list->next && (list->next->type == T_WORD) && (*is_command) == 0)
	{
		list->next->type = T_COMMAND;
		list = list->next;
		(*is_command) = 1;
	}
	return (list);
}

static void	process_token(t_shell *shell, t_token **list, int *index,
		int *is_command)
{
	if (*list && (*list)->type == T_WORD && (*index) == 0)
	{
		(*list)->type = T_COMMAND;
		(*is_command) = 1;
	}
	else if ((*list) && ((*list)->type >= T_REDIRECT_IN
			&& (*list)->type <= T_HEREDOC))
		(*list) = tokens_after_redirection(shell, (*list), is_command);
	else if ((*list) && (*list)->type == T_WORD)
		(*list)->type = T_ARGUMENT;
	(*index)++;
	if ((*list) && (((*list)->type == T_PIPE || (*list)->type == T_LOGICAND
				|| (*list)->type == T_LOGICOR)))
	{
		(*index) = 0;
		(*is_command) = 0;
	}
}

int	categorise_tokens(t_shell *shell)
{
	t_token	*current_token;
	int		token_index;
	int		is_command;

	current_token = shell->token_list;
	token_index = 0;
	is_command = 0;
	while (current_token)
	{
		process_token(shell, &current_token, &token_index, &is_command);
		if (!current_token)
			return (1);
		current_token = current_token->next;
	}
	return (0);
}
