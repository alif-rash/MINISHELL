/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 09:14:49 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 18:01:43 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*append_data(char *line, int index[2], char *result, int flag)
{
	char	*expansion;
	char	*new_result;

	expansion = ft_substr(line, index[1], index[0] - index[1] + flag);
	if (!expansion)
		expansion = ft_strdup("");
	new_result = ft_strjoin(result, expansion);
	free(result);
	free(expansion);
	return (new_result);
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
	while (str[index[0]] && str[index[0]] != quote_char)
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

char	*expand_variables_heredoc(char *line, int *index, t_shell *shell)
{
	char	*expanded;
	int		pos[2];

	pos[0] = *index;
	pos[1] = *index;
	expanded = ft_strdup("");
	while (line[pos[0]] && line[pos[0]] != '\'' && line[pos[0]] != '\"')
	{
		if (line[pos[0]] == '$')
		{
			expanded = handle_double_variable(line, pos, expanded, shell);
			pos[1] = pos[0];
		}
		else
			pos[0]++;
	}
	if (pos[1] < pos[0])
		expanded = append_data(line, pos, expanded, 0);
	*index = pos[0];
	return (expanded);
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
