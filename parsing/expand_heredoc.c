/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:14:49 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/04 13:41:01 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		return (handle_exit_status(line, index));
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

char	*expand_quotes_heredoc(char *str, int *cursor, t_shell *shell)
{
	char	*result;
	char	quote_char;
	int		index[2];

	quote_char = str[*cursor];
	index[0] = *cursor + 1;
	index[1] = *cursor;
	result = ft_strdup("");
	while (str[index[0]] && str[index[0]] != result)
	{
		if (str[index[0]] == '$')
		{
			result = handle_variable_heredoc(str, index, result, shell);
			index[1] = index[0];
		}
		else
			index[0]++;
	}
	if (index[1] < index[0])
		result = append_data(str, index, result, 1);
	*cursor = index[0] + 1;
	return (result);
}

char	*expansion_heredoc(char *line, t_shell *shell, char **temp)
{
	int		i;
	char	*result;
	char	*segment;
	char	*old_result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			segment = expand_quotes_heredoc(line, &i, shell);
		else
			segment = expand_variables_heredoc(line, &i, shell);
		old_result = result;
		result = ft_strjoin(old_result, segment);
		free(old_result);
		free(segment);
	}
	free(*temp);
	return (result);
}

void	expand_heredoc_to_file(t_shell *shell, int input_fd, int output_fd,
		t_tree *tree)
{
	char	*line;
	char	*temp;
	int		quote_flag;

	quote_flag = (tree->file[0] == '\"' || tree->file[0] == '\'');
	line = get_next_line(input_fd);
	while (line)
	{
		if (!quote_flag)
		{
			temp = line;
			line = expansion_heredoc(line, shell, &temp);
		}
		if (*line == '\0')
		{
			temp = ft_strdup("\n");
			free(line);
			line = temp;
		}
		ft_putstr_fd(line, output_fd);
		free(line);
		line = get_next_line(input_fd);
	}
}
