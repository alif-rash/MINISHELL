/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:36:07 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 09:38:11 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status(const char *line, int index[2])
{
	char	*exit_str;

	exit_str = ft_itoa(exit_status("exit status", -1));
	index[0]++;
	index[1] = index[0];
	while (line[index[0]] && line[index[0]] != ' ' && line[index[0]] != '"'
		&& line[index[0]] != '\'' && line[index[0]] != '$')
		index[0]++;
	exit_str = append_data(line, index, exit_str, 0);
	return (exit_str);
}

char	*get_env_value(t_env *env_list, const char *var_name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (!ft_strncmp(var_name, current->key, ft_strlen(var_name))
			&& ft_strlen(var_name) == ft_strlen(current->key) && current->value)
			return (ft_strdup(current->value));
		current = current->next;
	}
	return (ft_strdup(""));
}

char	*get_var(char *line, int *index, t_env *env_list)
{
	char	*var_name;
	int		start;
	char	*env_value;

	start = *index;
	var_name = NULL;
	while (line[*index] && (ft_isalnum(line[*index]) || line[*index] == '_'))
	{
		if (line[start] >= '0' && line[start] <= '9')
		{
			(*index)++;
			break ;
		}
		(*index)++;
	}
	if (*index > start)
	{
		var_name = ft_substr(line, start, *index - start);
		env_value = get_env_value(env_list, var_name);
		free(var_name);
	}
	else
		env_value = ft_strdup("");
	return (env_value);
}

char	*get_variable_value(char *line, int pos[2], t_shell *shell)
{
	char	*raw_variable_name;
	char	*clean_variable_name;

	pos[0]++;
	if (line[pos[0]] == '$')
	{
		pos[0]++;
		return (ft_strdup(""));
	}
	if (ft_isalnum(line[pos[0]]) || line[pos[0]] == '_')
	{
		raw_variable_name = get_var(line, &pos[0], shell->env_list);
		clean_variable_name = ft_substr(raw_variable_name, 1,
				ft_strlen(raw_variable_name) - 2);
		free(raw_variable_name);
		return (clean_variable_name);
	}
	else if (line[pos[0]] == '?')
		return (expand_exit_status(line, index));
	return (ft_strdup("$"));
}

char	*handle_variable_heredoc(char *line, int index[2], char *result,
		t_shell *shell)
{
	char	*text_before_variable;
	char	*variable_value;
	char	*temp;

	text_before_variable = ft_substr(line, index[1], index[0] - index[1]);
	variable_value = get_variable_value(line, index, shell);
	temp = ft_strjoin(result, text_before_variable);
	free(result);
	result = ft_strjoin(temp, variable_value);
	free(temp);
	if (line[index[0]] == '\"' || line[index[0]] == '\'')
	{
		if (line[index[0]] == '\"')
			temp = ft_strjoin(result, "\"");
		else
			temp = ft_strjoin(result, "\'");
		free(result);
		result = temp;
	}
	free(text_before_variable);
	free(variable_value);
	return (result);
}
