/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:04:20 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/04 13:29:58 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_space(const char *s)
{
	while (*s && *s != ')')
	{
		if (!is_token(*s, T_SPACE))
			return (0);
		s++;
	}
	return (1);
}

int ft_isnumeric(const char *str)
{
	if (!str || !(*str))
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}