/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:02:28 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/11 11:20:49 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*create_token(t_shell *shell, int index, int type, char *str)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (new_node)
	{
		new_node->value = ft_substr(str, shell->index - index, index);
		new_node->type = type;
		new_node->next = NULL;
		new_node->fd = -1;
	}
	return (new_node);
}

t_token	*ft_token_last(t_token *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

void	token_add_back(t_token **list, t_token *new)
{
	t_token	*last_node;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last_node = ft_token_last(*list);
	last_node->next = new;
}

void	ft_free_tokenlist(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
		if (current->value)
			free(current->value);
		if (current->fd > 0)
		{
			close(current->fd);
			current->fd = -1;
		}	
		free(current);
		current = next;
	}
	*token_list = NULL;
}

void	ft_free_envlist(t_env **env_list)
{
	t_env	*current;
	t_env	*next;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	while (current)
	{
		if (current->next)
			next = current->next;
		else
			next = NULL;
		free(current->env);
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*env_list = NULL;
}
