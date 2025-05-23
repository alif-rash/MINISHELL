/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:57:48 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/23 10:58:13 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_function(void **a, void **b, void **c, void **d)
{
	if (a && *a)
	{
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	if (c && *c)
	{
		free(*c);
		*c = NULL;
	}
	if (d && *d)
	{
		free(*d);
		*d = NULL;
	}
}
