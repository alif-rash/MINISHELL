/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:45:56 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/09 17:32:15 by hparveen         ###   ########.fr       */
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
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				shell->env_list = curr->next;
			free(curr->key);
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
	int i = 1;

	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(shell, args[i]);
		else
			ft_perror("unset", "invalid identifier");
		i++;
	}
	return (0);
}