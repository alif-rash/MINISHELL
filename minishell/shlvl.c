/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:26 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/20 13:14:34 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_return_shlvl(char *value)
{
	int					index;
	int					sign;
	unsigned long long	number;

	index = 0;
	sign = 1;
	number = 0;
	skip_spaces(&value, &index, &sign);
	while (value[index] >= '0' && value[index] <= '9')
	{
		number = number * 10 + (value[index] - '0');
		if ((sign == 1 && number > 9223372036854775807ULL) || (sign == -1
				&& number > 9223372036854775808ULL))
			return (ft_strdup("1"));
		index++;
	}
	if (sign == 1 && number == 9223372036854775807ULL)
		return (ft_strdup("0"));
	number++;
	if ((sign == 1 && number > 9223372036854775807ULL) || (sign == -1
			&& number > 9223372036854775808ULL))
		return (ft_strdup("1"));
	return (ft_itoa(sign * (int)number));
}
