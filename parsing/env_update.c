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

#include "../minishell.h"

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

/**
 * @brief Find environment variable by name
 * @param shell Shell structure
 * @param name Environment variable name
 * @return Pointer to environment variable node or NULL if not found
 */
static t_env	*find_env_var(t_shell *shell, const char *name)
{
	t_env	*curr;

	curr = shell->env_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/**
 * @brief Update PWD and OLDPWD environment variables
 * @param shell Shell structure
 * @param oldpwd Previous working directory
 * @param newpwd New working directory
 * @return 0 on success
 */
static int	update_pwd_vars(t_shell *shell, char *oldpwd, char *newpwd)
{
	t_env	*pwd_var;
	t_env	*oldpwd_var;

	if (oldpwd)
	{
		oldpwd_var = find_env_var(shell, "OLDPWD");
		if (oldpwd_var)
			update_env(shell, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (newpwd)
	{
		pwd_var = find_env_var(shell, "PWD");
		if (pwd_var)
			update_env(shell, "PWD", newpwd);
		free(newpwd);
	}
	return (0);
}
