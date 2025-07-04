/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 08:39:29 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/12 10:00:46 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_and_null(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	add_subtree_to_struct(t_shell *shell, t_tree *subtree)
{
	t_subtree	*new_subtree;
	t_subtree	*current;

	if (!shell || !subtree)
		return ;
	new_subtree = malloc(sizeof(t_subtree));
	if (!new_subtree)
		return ;
	new_subtree->tree = subtree;
	new_subtree->next = NULL;
	if (!shell->subtree)
	{
		shell->subtree = new_subtree;
		return ;
	}
	current = shell->subtree;
	while (current->next)
		current = current->next;
	current->next = new_subtree;
}

static void	ft_parsing_subshell(t_shell *shell, t_tree **subtree)
{
	char	*trimmed;
	t_token	*tokens;

	trimmed = trim_brackets(shell->prompt);
	if (trimmed[0] == '\0')
		return (free(trimmed), free(shell->prompt));
	free_and_null(&shell->prompt);
	shell->index = 0;
	if (tokenisation(shell, trimmed))
	{
		free(trimmed);
		return ;
	}
	free_and_null(&trimmed);
	if (categorise_tokens(shell))
		return ;
	if (check_syntax(shell))
		return ;
	tokens = shell->token_list;
	heredoc(shell, tokens);
	(*subtree) = build_ast(&tokens);
	if (shell->ast == NULL)
		return (handle_error(shell, "tree_create", ERROR_SYNTAX, '\0'));
	ft_free_tokenlist(&shell->token_list);
}

void	execute_subshell(t_shell *shell, t_tree *tree)
{
	t_tree	*subtree;

	subtree = NULL;
	if (!tree || tree->type != T_BRACKET || !tree->file)
		return ;
	shell->prompt = ft_strdup(tree->file);
	ft_parsing_subshell(shell, &subtree);
	if (!subtree)
		return ;
	add_subtree_to_struct(shell, subtree);
	execute(shell, subtree);
}
