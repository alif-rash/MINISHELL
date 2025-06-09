/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:31:42 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 12:52:57 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_double_variable(char *input, int pos[2], char *result,
		t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	var_name = NULL;
	temp = NULL;
	var_value = NULL;
	var_name = ft_substr(input, pos[1], pos[0] - pos[1]);
	if (!var_name)
		var_name = ft_strdup("");
	var_value = get_variable_value(input, pos, shell);
	temp = ft_strjoin(result, var_name);
	if (result)
		free(result);
	result = ft_strjoin(temp, var_value);
	free(temp);
	free(var_name);
	free(var_value);
	return (result);
}

static char	*expand_d_quotes(char *input, int *pos, t_shell *shell)
{
	char	*result;
	int		index[2];

	index[0] = *pos + 1;
	index[1] = *pos;
	result = ft_strdup("");
	while (input[pos[0]] && input[pos[0]] != '\"')
	{
		if (input[index[0]] == '$')
		{
			result = handle_double_variable(input, index, result, shell);
			index[1] = index[0];
		}
		else
			index[0]++;
	}
	if (index[1] < index[0] || input[index[0]] == '\"')
		result = append_data(input, index, result, 1);
	*pos = index[0] + 1;
	return (result);
}

static char	*expand_s_quotes(char *input, int *pos)
{
	char	*result;
	int		i;

	i = *pos + 1;
	result = ft_strdup("");
	while (input[i] && input[i] != '\'')
		i++;
	result = ft_substr(input, *pos, i - *pos + 1);
	*pos = i + 1;
	return (result);
}

char	*expand_variables(char *input, int *pos, t_shell *shell)
{
	char	*result;
	int		index[2];

	index[0] = *pos;
	index[1] = *pos;
	result = ft_strdup("");
	while (input[index[0]] && input[index[0]] != '\"' && input[index[0]] != '\'')
		result = expand_special_characters(input, index, result, shell);
	if (index[1] < index[0])
		result = append_data(input, index, result, 0);
	*pos = index[0];
	return (result);
}

char	*process_expansion(char *input, t_shell *shell)
{
	int		pos;
	char	*result;
	char	*segment;
	char	*temp;

	pos = 0;
	result = ft_strdup("");
	segment = NULL;
	temp = NULL;
	while (input[pos])
	{
		if (input[pos] == '\"')
			segment = expand_d_quotes(input, &pos, shell);
		else if (input[pos] == '\'')
			segment = expand_s_quotes(input, &pos);
		else
			segment = expand_variables(input, &pos, shell);
		temp = result;
		result = ft_strjoin(temp, segment);
		free(temp);
		free(segment);
	}
	return (result);
}
