/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:20:52 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 08:21:03 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_shell *shell, const char *key, const char *value)
{
	t_env	*current;
	int		found;

	if (!shell || !key || !value)
		return ;
	found = 0;
	current = shell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			found = 1;
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				perror("Error updating environment variable");
			return ;
		}
		current = current->next;
	}
	if (!found)
		new_env(shell, ft_strdup(key), ft_strdup(value), 1);
}
