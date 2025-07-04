/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:36:05 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/13 10:33:24 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Check if string contains only whitespace characters
 * @param str String to check
 * @return 1 if only whitespace, 0 otherwise
 */
static int	is_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Check if expansion should be marked for removal
 * @param original Original string before expansion
 * @param expanded Expanded string after processing
 * @return 1 if should be marked, 0 otherwise
 */
static int	should_mark_expanded(char *original, char *expanded)
{
	if (!expanded || ft_strcmp(original, expanded) == 0)
		return (0);
	if (expanded[0] != '\0' && !is_only_space(expanded))
		return (1);
	if (original[0] == '$')
		return (1);
	return (0);
}

int	expand_command(t_shell *shell, t_tree *tree)
{
	int		i;
	char	*expanded_argument;
	int		is_expanded;

	i = 0;
	is_expanded = 0;
	while (tree->args[i])
	{
		expanded_argument = process_expansion(tree->args[i], shell);
		expanded_argument = clean_all_quotes(expanded_argument);
		if (should_mark_expanded(tree->args[i], expanded_argument))
			is_expanded = 1;
		free(tree->args[i]);
		tree->args[i] = ft_strdup(expanded_argument);
		if (expanded_argument)
		{
			free(expanded_argument);
			expanded_argument = NULL;
		}
		if (!tree->args[i])
			return (is_expanded);
		i++;
	}
	return (is_expanded);
}
