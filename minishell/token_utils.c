/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:50:00 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/24 12:09:43 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator_type(int is_double, char current)
{
	if (!is_double)
	{
		if (current == '|')
			return (T_PIPE);
		else if (current == '<')
			return (T_REDIRECT_IN);
		else if (current == '>')
			return (T_REDIRECT_OUT);
	}
	else
	{
		if (current == '|')
			return (T_LOGICOR);
		else if (current == '&')
			return (T_LOGICAND);
		else if (current == '<')
			return (T_HEREDOC);
		else if (current == '>')
			return (T_APPEND);
	}
	return (0);
}

int	brackets_closed(char *str, t_shell *shell, int *start, int *end)
{
	int	nesting_level;

	nesting_level = 0;
	*start = -1;
	*end = -1;
	while (str[shell->index])
	{
		if (str[shell->index] == '(')
		{
			if (nesting_level++ == 0)
				*start = shell->index;
		}
		else if (str[shell->index] == ')')
		{
			if (--nesting_level == 0)
			{
				*end = shell->index;
				shell->index++;
				return (1);
			}
		}
		shell->index++;
	}
	return (0);
}
