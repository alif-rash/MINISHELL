/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:32 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/24 13:38:44 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	skip_spaces(char **str, int *i, int *sign)
{
	if (!(*str))
		return ;
	while ((*str)[*i] == ' ' || ((*str)[*i] >= 9 && (*str)[*i] <= 13))
		(*i)++;
	if ((*str)[*i] == '-' || (*str)[*i] == '+')
	{
		if ((*str)[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isoperator(int c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}
