/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:36:05 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 18:44:22 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_command(t_shell *shell, t_tree *tree)
{
	int		i;
	char	*expanded_argument;

	i = 0;
	while (tree->args[i])
	{
		expanded_argument = process_expansion(tree->args[i], shell);
		expanded_argument = clean_all_quotes(expanded_argument);
		free(tree->args[i]);
		tree->args[i] = ft_strdup(expanded_argument);
		if (expanded_argument)
		{
			free(expanded_argument);
			expanded_argument = NULL;
		}
		if (!tree->args[i])
			return ;
		i++;
	}
}
