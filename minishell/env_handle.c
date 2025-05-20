/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:07 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/20 13:48:35 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*shlvl_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!((value[i] >= '0' && value[i] <= '9') || (value[0] == '-')
				|| (value[0] == '+')))
			return (ft_strdup("\"1\""));
		i++;
	}
	return (ft_return_shlvl(value));
}

void	update_shlvl(t_shell *shell)
{
	t_env	*env_node;
	char	*updated_value;

	env_node = shell->env_list;
	updated_value = NULL;
	while (env_node)
	{
		if (ft_strcmp(env_node->key, "SHLVL") == 0)
		{
			env_node->flag = 1;
			if (env_node->value == NULL)
				env_node->value = ft_strdup("\"1\"");
			else
			{
				updated_value = shlvl_value(env_node->value);
				free(env_node->value);
				env_node->value = updated_value;
			}
			break ;
		}
		env_node = env_node->next;
	}
	if (!search_in_env(shell, "SHLVL"))
		new_env(shell, ft_strdup("SHLVL"), ft_strdup("\"1\""), 1);
}

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

void	new_env(t_shell *shell, char *key, char *value, int export_flag)
{
	char	*env_str;
	char	*key_with_equal;

	env_str = NULL;
	key_with_equal = NULL;
	if (export_flag)
		key_with_equal = ft_strjoin(key, "=");
	else
		key_with_equal = ft_strdup(key);
	if (export_flag && value)
		env_str = ft_strjoin(key_with_equal, value);
	else
		env_str = ft_strdup(key_with_equal);
	if (value)
		free(value);
	free(key);
	free(key_with_equal);
	env_lstadd_back(&shell->env_list, envlst_new(env_str, export_flag));
	free(env_str);
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
		if (ft_strcmp(env_node->value, "OLDPWD") == 0)
		{
			env_node->flag = 0;
			if (env_node->value)
				free(env_node->value);
			env_node->value = NULL;
		}
		env_node = env_node->next;
	}
}
