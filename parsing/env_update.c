/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:52 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/12 13:36:49 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_shell *shell, char *key, char *value)
{
	t_env	*current;
	char	*new_val;

	if (!shell || !key || !value)
		return ;
	current = shell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			current->flag = 1;
			if (ft_strcmp(key, "PWD") == 0 || ft_strcmp(key, "OLDPWD") == 0)
				new_val = ft_strdup(value);
			else
				new_val = add_quote(value);
			free(current->value);
			current->value = ft_strdup(new_val);
			if (!current->value)
				perror("Error updating environment variable");
			return (free(new_val), (void)0);
		}
		current = current->next;
	}
	if (current->flag == 0)
		new_env(shell, ft_strdup(key), ft_strdup(value), current->flag == 1);
}
