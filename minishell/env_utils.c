/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:12 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/20 13:49:52 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_function(void **a, void **b, void **c, void **d)
{
	if (a && *a)
	{
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	if (c && *c)
	{
		free(*c);
		*c = NULL;
	}
	if (d && *d)
	{
		free(*d);
		*d = NULL;
	}
}

char	*add_quote(char *str)
{
	char	*quoted_string;
	int		len;

	len = ft_strlen(str);
	quoted_string = malloc(len + 3);
	if (!quoted_string)
		return (NULL);
	quoted_string[0] = '"';
	ft_strcpy(quoted_string + 1, str);
	quoted_string[len + 1] = '"';
	quoted_string[len + 2] = '\0';
	return (quoted_string);
}

int	assign_value(t_env **env_node, char *env_variable, int *start_index)
{
	char	*quoted;

	(*env_node)->value = ft_substr(env_variable, *start_index,
			ft_strlen(env_variable) - *start_index);
	if (!(*env_node)->value)
		return (free_function((void **)&(*env_node)->key,
				(void **)&(*env_node)->env, NULL, NULL), 1);
	quoted = add_quote((*env_node)->value);
	if (!quoted)
	{
		free((*env_node)->value);
		return (free_function((void **)&(*env_node)->key,
				(void **)&(*env_node)->env, (void **)&(*env_node), NULL), 1);
	}
	free((*env_node)->value);
	(*env_node)->value = quoted;
	return (0);
}

int	parse_key_value(char *env_variable, int flag, t_env **env_node, int *index)
{
	while (env_variable[(*index)] && env_variable[(*index)] != '=')
		(*index)++;
	(*env_node)->key = ft_substr(env_variable, 0, *index);
	if (!(*env_node)->key)
		return (free_function((void **)&((*env_node)->env), (void **)env_node,
				NULL, NULL), 1);
	if (env_variable[(*index)])
		(*index)++;
	if (env_variable[(*index)])
	{
		if (assign_value(env_node, env_variable, index))
			return (1);
	}
	else
		(*env_node)->value = NULL;
	(*env_node)->flag = flag;
	return ((*env_node)->next = NULL, 0);
}

void	env_lstadd_back(t_env **env_list, t_env *new_node)
{
	t_env	*last_node;

	if (env_list == NULL)
		return ;
	if (*env_list == NULL)
	{
		*env_list = new_node;
		return ;
	}
	last_node = *env_list;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
}
