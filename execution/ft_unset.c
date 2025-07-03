/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:45:56 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/25 10:19:15 by hparveen         ###   ########.fr       */
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

/**
 * @brief Remove environment variable from shell environment list
 * @param shell Shell structure containing environment list
 * @param name Name of environment variable to remove
 */
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
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			free(curr->env);
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
	int	ret;

	i = 1;
	ret = 0;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(shell, args[i]);
		else
		{
			handle_error(shell, args[i], ERROR_GENERIC, INVALID_IDENTIFIER);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
