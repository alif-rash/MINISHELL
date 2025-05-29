/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:10:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/29 13:39:41 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*create_tree(t_token **tokens)
{
	return (create_tree_and(tokens));
}

t_tree	*create_tree_and(t_token **tokens)
{
	t_tree	*new_node;
	t_tree	*left;

	left = create_tree_or(tokens);
	if (!(*tokens) || (*tokens)->type != T_LOGICAND)
		return (left);
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->type = T_LOGICAND;
	new_node->left = left;
	new_node->right = NULL;
	new_node->args = NULL;
	new_node->fd = -1;
	new_node->file = NULL;
	*tokens = (*tokens)->next;
	new_node->right = create_tree_and(tokens);
	return (new_node);
}

t_tree	*create_tree_or(t_token **tokens)
{
	t_tree	*new_node;
	t_tree	*left;

	left = create_tree_pipe(tokens);
	if (!(*tokens) || (*tokens)->type != T_LOGICOR)
		return (left);
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->fd = -1;
	new_node->file = NULL;
	new_node->left = left;
	new_node->right = NULL;
	new_node->type = T_LOGICOR;
	*tokens = (*tokens)->next;
	new_node->right = create_tree_or(tokens);
	return (new_node);
}

t_tree	*create_tree_pipe(t_token **tokens)
{
	t_tree	*new_node;
	t_tree	*left;

	left = create_tree_redirections(tokens);
	if (!(*tokens) || (*tokens)->type != T_PIPE)
		return (left);
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		return (NULL);
	new_node->args = NULL;
	new_node->fd = -1;
	new_node->file = NULL;
	new_node->left = left;
	new_node->right = NULL;
	new_node->type = T_PIPE;
	*tokens = (*tokens)->next;
	new_node->right = create_tree_pipe(tokens);
	return (new_node);
}
