/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:47:28 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 18:44:16 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create substring with quotes removed
 * @param result Original string containing quotes
 * @param count Length of string without quotes
 * @return New string with quotes removed
 */
static char	*substring_without_quotes(char *result, int count)
{
	char	*new_result;
	int		i;
	char	quote;

	new_result = malloc(sizeof(char) * (count + 1));
	if (!new_result)
		return (NULL);
	i = 0;
	count = 0;
	while (result[i])
	{
		if (result[i] == '\'' || result[i] == '\"')
		{
			quote = result[i++];
			while (result[i] && result[i] != quote)
				new_result[count++] = result[i++];
			if (result[i] == quote)
				i++;
		}
		else
			new_result[count++] = result[i++];
	}
	new_result[count] = '\0';
	return (new_result);
}

/**
 * @brief Count characters in string excluding quotes
 * @param result String to count
 * @param count Pointer to store character count
 */
static void	ft_count_without_quotes(char *result, int *count)
{
	char	quote;
	int		i;

	i = 0;
	while (result[i])
	{
		if (result[i] == '\'' || result[i] == '\"')
		{
			quote = result[i++];
			while (result[i] && result[i] != quote)
			{
				(*count)++;
				i++;
			}
			if (result[i] == quote)
				i++;
		}
		else
		{
			(*count)++;
			i++;
		}
	}
}

char	*clean_all_quotes(char *result)
{
	char	*new_result;
	int		count_without_quotes;

	count_without_quotes = 0;
	ft_count_without_quotes(result, &count_without_quotes);
	new_result = substring_without_quotes(result, count_without_quotes);
	free(result);
	return (new_result);
}

int	expand_redirection(t_shell *shell, t_tree *tree)
{
	char	*result;

	result = process_expansion(tree->file, shell);
	if (*result == '\0')
		handle_error(shell, tree->file, ERROR_GENERIC, 2);
	result = clean_all_quotes(result);
	free(tree->file);
	tree->file = ft_strdup(result);
	free(result);
	return (0);
}
