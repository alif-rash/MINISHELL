/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:46:54 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/09 17:30:51 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *env_list)
{
	t_env	*current;
	char	*value;

	if (!env_list)
		return (0);
	current = env_list;
	while (current)
	{
		if (current->value && current->flag == 1)
		{
			value = remove_quotes(current->value);
			printf("%s=%s\n", current->key, value);
		}
		current = current->next;
	}
	return (0);
}
