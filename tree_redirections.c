/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:05:08 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/30 09:23:12 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_redirection_node(t_tree **redir_node, t_token **tokens,
		int *has_prev_redir)
{
	*has_prev_redir = 1;
	*redir_node = malloc(sizeof(t_tree));
	if (!*redir_node)
		return ;
	(*redir_node)->args = NULL;
	(*redir_node)->fd = (*tokens)->fd;
	(*redir_node)->type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == T_FILENAME
			|| (*tokens)->type == T_DELIMITER))
		(*redir_node)->file = ft_strdup((*tokens)->value);
}

void	append_redirection_to_chain(t_tree **prev_redir, t_tree **new_node,
		t_tree **head)
{
	if (*prev_redir)
		(*prev_redir)->lhs = *new_node;
	else
		*head = *new_node;
	*prev_redir = *new_node;
}

void	skip_filename_and_args(t_tree **cmd_node, t_token **tokens,
		t_tree **redir_node)
{
	if (*tokens && ((*tokens)->type == T_FILENAME
			|| (*tokens)->type == T_DELIMITER))
		*tokens = (*tokens)->next;
	while (*tokens && ((*tokens)->type == T_COMMAND
			|| (*tokens)->type == T_ARGUMENT))
	{
		if ((*tokens)->type == T_COMMAND && !(*cmd_node))
		{
			*cmd_node = build_ast_command(tokens);
			continue ;
		}
		*tokens = (*tokens)->next;
	}
	(*redir_node)->rhs = NULL;
}
