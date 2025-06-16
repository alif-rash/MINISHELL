/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:59:21 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/16 09:00:24 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_username(char *input, int pos[2])
{
	int		length;
	char	*username;

	length = 1;
	username = NULL;
	while (input[length] && input[length] != '/')
	{
		if (input[length] == '\"' || input[length] == '\'')
		{
			pos[0] += length;
			return (ft_substr(input, 0, length));
		}
		length++;
	}
	pos[0] += length;
	username = ft_substr(input, 1, length - 1);
	if (!username)
		username = ft_strdup("");
	return (username);
}

char	*ft_get_variable_value(char *input, int pos[2], t_shell *shell)
{
	if (!input[pos[0] + 1])
	{
		pos[0]++;
		return (ft_strdup("$"));
	}
	pos[0]++;
	if (input[pos[0]] == '$')
	{
		pos[0]++;
		return (ft_strdup(""));
	}
	if (ft_isalnum(input[pos[0]]) || input[pos[0]] == '_')
		return (get_var(input, &pos[0], shell->env_list));
	else if (input[pos[0]] == '?')
		return (expand_exit_status(input, pos));
	return (ft_strdup(""));
}

char	*handle_variable(char *input, int pos[2], char *result, t_shell *shell)
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
	var_value = ft_get_variable_value(input, pos, shell);
	temp = ft_strjoin(result, var_name);
	if (result)
		free(result);
	result = ft_strjoin(temp, var_value);
	free(temp);
	free(var_name);
	free(var_value);
	return (result);
}

char	*get_quote_variable_value(char *input, int pos[2], t_shell *shell)
{
	pos[0]++;
	if (input[pos[0]] == '$')
	{
		pos[0]++;
		return (ft_strdup("$"));
	}
	if (ft_isalnum(input[pos[0]]) || input[pos[0]] == '_')
		return (get_var(input, &pos[0], shell->env_list));
	else if (input[pos[0]] == '?')
		return (expand_exit_status(input, pos));
	return (ft_strdup("$"));
}

char	*handle_quotes_variable(char *input, int pos[2], char *result,
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
	var_value = get_quote_variable_value(input, pos, shell);
	temp = ft_strjoin(result, var_name);
	if (result)
		free(result);
	result = ft_strjoin(temp, var_value);
	free(temp);
	free(var_name);
	free(var_value);
	return (result);
}
