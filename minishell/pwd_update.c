/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:07:17 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/26 09:07:51 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_env(t_shell *shell, char *key)
{
	t_env	*temp;

	temp = shell->env_list;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	init_pwd_oldpwd(t_shell *shell)
{
	t_env	*env_node;
	char	cwd[1024];

	env_node = shell->env_list;
	if (search_in_env(shell, "PWD") == NULL)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			return ;
		new_env(shell, ft_strdup("PWD"), ft_strdup(cwd), 1);
	}
	if (search_in_env(shell, "OLDPWD") == NULL)
		new_env(shell, ft_strdup("OLDPWD"), NULL, 0);
	while (env_node)
	{
		if (ft_strcmp(env_node->key, "OLDPWD") == 0)
		{
			env_node->flag = 0;
			if (env_node->value)
				free(env_node->value);
			env_node->value = NULL;
		}
		env_node = env_node->next;
	}
}
