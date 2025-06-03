/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 09:05:08 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 08:19:01 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	build_redirection_node(t_tree **redir_node, t_token **tokens,
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

static void	append_redirection_to_chain(t_tree **prev_redir, t_tree **new_node,
		t_tree **head)
{
	if (*prev_redir)
		(*prev_redir)->lhs = *new_node;
	else
		*head = *new_node;
	*prev_redir = *new_node;
}

static void	skip_filename_and_args(t_tree **cmd_node, t_token **tokens,
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

t_tree	*build_ast_redirections(t_token **tokens)
{
	t_tree	*command_node;
	t_tree	*redir_node;
	t_tree	*prev_redir;
	t_tree	*first_redir;
	int		redir[2];

	redir[0] = 0;
	redir[1] = 0;
	prev_redir = NULL;
	first_redir = NULL;
	command_node = build_ast_command(tokens);
	while (*tokens && ((*tokens)->type >= T_REDIRECT_IN
			&& (*tokens)->type <= T_HEREDOC))
	{
		build_redirection_node(&redir_node, tokens, &redir[1]);
		append_redirection_to_chain(&prev_redir, &redir_node, &first_redir);
		skip_filename_and_args(&command_node, tokens, &redir_node);
		redir[0]++;
	}
	if (redir[1])
		redir_node->lhs = command_node;
	if (redir[0] == 0)
		return (command_node);
	return (first_redir);
}
