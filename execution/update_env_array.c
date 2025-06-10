/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 08:44:00 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/10 09:25:50 by hparveen         ###   ########.fr       */
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

static void	fill_env_variable(char *env_var, t_env *env_list, char *value,
		int key_len, int value_len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < key_len)
		env_var[i++] = env_list->key[j++];
	env_var[i++] = '=';
	j = 0;
	while (j < value_len)
		env_var[i++] = value[j++];
	env_var[i] = '\0';
}

static void	initialize_lengths(int *key_len, int *value_len, t_env *env_list)
{
	*key_len = ft_strlen(env_list->key);
	*value_len = 0;
}

static void	build_env_array(t_env *env_list, char **env_array, int count)
{
	int		index;
	int		key_len;
	int		value_len;
	char	*trimmed_value;

	index = 0;
	while (index < count)
	{
		initialize_lengths(&key_len, &value_len, env_list);
		trimmed_value = NULL;
		if (env_list->value)
			trimmed_value = get_trimmed_value(env_list, &value_len);
		env_array[index] = malloc((key_len + value_len + 2) * sizeof(char));
		if (!env_array[index])
			return ;
		fill_env_variable(env_array[index], env_list, trimmed_value, key_len,
			value_len);
		if (trimmed_value)
			free(trimmed_value);
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
