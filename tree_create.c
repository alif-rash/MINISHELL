/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:10:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/30 08:55:32 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*build_ast(t_token **tokens)
{
	return (build_ast_and(tokens));
}

t_tree	*build_ast_and(t_token **tokens)
{
	t_tree	*branch;
	t_tree	*lhs;

	lhs = build_ast_or(tokens);
	if (!(*tokens) || (*tokens)->type != T_LOGICAND)
		return (lhs);
	branch = malloc(sizeof(t_tree));
	if (!branch)
		return (NULL);
	branch->type = T_LOGICAND;
	branch->lhs = lhs;
	branch->rhs = NULL;
	branch->args = NULL;
	branch->fd = -1;
	branch->file = NULL;
	*tokens = (*tokens)->next;
	branch->rhs = build_ast_and(tokens);
	return (branch);
}

t_tree	*build_ast_or(t_token **tokens)
{
	t_tree	*branch;
	t_tree	*lhs;

	lhs = build_ast_pipe(tokens);
	if (!(*tokens) || (*tokens)->type != T_LOGICOR)
		return (lhs);
	branch = malloc(sizeof(t_tree));
	if (!branch)
		return (NULL);
	branch->args = NULL;
	branch->fd = -1;
	branch->file = NULL;
	branch->lhs = lhs;
	branch->rhs = NULL;
	branch->type = T_LOGICOR;
	*tokens = (*tokens)->next;
	branch->rhs = build_ast_or(tokens);
	return (branch);
}

t_tree	*build_ast_pipe(t_token **tokens)
{
	t_tree	*branch;
	t_tree	*lhs;

	lhs = build_ast_redirections(tokens);
	if (!(*tokens) || (*tokens)->type != T_PIPE)
		return (lhs);
	branch = malloc(sizeof(t_tree));
	if (!branch)
		return (NULL);
	branch->args = NULL;
	branch->fd = -1;
	branch->file = NULL;
	branch->lhs = lhs;
	branch->rhs = NULL;
	branch->type = T_PIPE;
	*tokens = (*tokens)->next;
	branch->rhs = build_ast_pipe(tokens);
	return (branch);
}

t_tree	*build_ast_redirections(t_token **tokens)
{
	t_tree	*command_node;
	t_tree	*redir_node;
	t_tree	*prev_redir;
	t_tree	*first_redir;
	int		redir_count;
	int		has_prev_redir;

	redir_count = 0;
	has_prev_redir = 0;
	prev_redir = NULL;
	first_redir = NULL;
	command_node = build_ast_command(tokens);
	while (*tokens && (*tokens)->type >= T_REDIRECT_IN
		&& (*tokens) <= T_HEREDOC)
	{
		build_redirection_node(&redir_node, tokens, &has_prev_redir);
		append_redirection_to_chain(&prev_redir, &redir_node, &first_redir);
		skip_filename_and_args(&command_node, tokens, &redir_node);
		redir_count++;
	}
	if (has_prev_redir)
		redir_node->lhs = command_node;
	if (redir_count == 0)
		return (command_node);
	return (first_redir);
}
