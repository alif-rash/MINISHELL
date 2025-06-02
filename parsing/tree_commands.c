/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:11:57 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/02 17:20:44 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_command_args(t_token *token)
{
	int	count;

	count = 0;
	while (token && (token->type == T_COMMAND || token->type == T_ARGUMENT
			|| token->type == T_FILENAME || token->type == T_DELIMITER
			|| (token->type >= T_REDIRECT_IN && token->type <= T_HEREDOC)))
	{
		if (token->type == T_COMMAND || token->type == T_ARGUMENT)
			count++;
		token = token->next;
	}
	return (count);
}

void skip_and_init(t_tree *node, t_token **tokens)
{
	while(*tokens && ((*tokens)->type == T_COMMAND || (*tokens)->type == T_ARGUMENT))
		*tokens = (*tokens)->next;
	node->fd = -1;
	node->file = NULL;
	node->lhs = NULL;
	node->rhs = NULL;
}
static void	fill_command_node(t_tree *node, t_token **tokens)
{
	t_token	*temp;
	int		i;

	temp = *tokens;
	i = count_command_args(temp);
	node->type = T_COMMAND;
	node->args = NULL;
	if (i > 0)
	{
		node->args = malloc(sizeof(char *) * (i + 1));
		if (!node->args)
			return ;
		i = 0;
		while(temp && (temp->type == T_COMMAND || temp->type == T_ARGUMENT 
			|| temp->type == T_FILENAME || temp->type == T_DELIMITER ||
			 (temp->type >= T_REDIRECT_IN  && temp->type <= T_HEREDOC)))
		{
			if(temp->type ==T_COMMAND || temp->type == T_ARGUMENT)
				node->args[i++] = ft_strdup(temp->value);
			temp = temp->next;
		}
		node->args[i] = NULL;
	}
	skip_and_init(node, tokens);
}

t_tree	*build_ast_command(t_token **tokens)
{
	t_tree	*cmd_node;

	if (!tokens || !(*tokens))
		return (NULL);
	if ((*tokens)->type == T_BRACKET || (*tokens)->type == T_COMMAND)
	{
		cmd_node = malloc(sizeof(t_tree));
		if (!cmd_node)
			return (NULL);
		if ((*tokens)->type == T_BRACKET)
		{
			cmd_node->type = T_BRACKET;
			cmd_node->file = ft_strdup((*tokens)->value);
			cmd_node->args = NULL;
			cmd_node->lhs = NULL;
			cmd_node->rhs = NULL;
			cmd_node->fd = -1;
			*tokens = (*tokens)->next;
		}
		else if ((*tokens)->type == T_COMMAND)
			fill_command_node(cmd_node, tokens);
		return (cmd_node);
	}
	return (NULL);
}
