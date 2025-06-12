/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:45:56 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/12 14:10:23 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(t_shell *shell, const char *name)
{
	t_env	*curr;
	t_env	*prev;

	curr = shell->env_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
		{
			if (ft_strcmp(name, "PWD") == 0 || ft_strcmp(name, "OLDPWD") == 0)
			{
				if (curr->value)
				{
					free(curr->value);
					curr->value = NULL;
				}
				curr->flag = 0;
				return ;
			}
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(shell, args[i]);
		else
			return (handle_error(shell, args[1], ERROR_GENERIC,
					INVALID_IDENTIFIER), 1);
		i++;
	}
	return (0);
}
