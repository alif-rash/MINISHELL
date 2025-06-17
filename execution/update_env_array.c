/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:44:00 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/17 08:50:23 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_trimmed_value(t_env *env_list, int *value_len)
{
	char	*trimmed;

	trimmed = ft_strtrim_sides(env_list->value);
	if (!trimmed)
		return (NULL);
	*value_len = ft_strlen(trimmed);
	return (trimmed);
}

static void	fill_env_variable(char *env_var, char *key, char *value)
{
	int	i;
	int	j;
	int	key_len;
	int	value_len;

	i = 0;
	j = 0;
	key_len = ft_strlen(key);
	value_len = 0;
	if (value)
		value_len = ft_strlen(value);
	while (j < key_len)
		env_var[i++] = key[j++];
	env_var[i++] = '=';
	j = 0;
	while (j < value_len)
		env_var[i++] = value[j++];
	env_var[i] = '\0';
}

static char	*create_new_env_entry(t_env *env_list)
{
	int		key_len;
	int		value_len;
	char	*trimmed_value;
	char	*env_variable;

	key_len = ft_strlen(env_list->key);
	value_len = 0;
	trimmed_value = get_trimmed_value(env_list, &value_len);
	env_variable = malloc(sizeof(char) * (key_len + value_len + 2));
	if (!env_variable)
	{
		if (trimmed_value)
			free(trimmed_value);
		return (NULL);
	}
	fill_env_variable(env_variable, env_list->key, trimmed_value);
	if (trimmed_value)
		free(trimmed_value);
	return (env_variable);
}

static void	build_env_array(t_env *env_list, char **env_array, int count)
{
	int		index;
	char	*env_variable;

	index = 0;
	while (index < count && env_list)
	{
		env_variable = create_new_env_entry(env_list);
		if (!env_variable)
			return ;
		env_array[index] = env_variable;
		env_list = env_list->next;
		index++;
	}
	env_array[index] = NULL;
}

void	update_env_array(t_shell *shell, t_env *env_list, int total_vars)
{
	char	**new_array;

	new_array = malloc(sizeof(char *) * (total_vars + 1));
	if (!new_array)
	{
		perror("malloc");
		return ;
	}
	build_env_array(env_list, new_array, total_vars);
	if (shell->env_array)
		ft_free_array(shell->env_array);
	shell->env_array = new_array;
}
