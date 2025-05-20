/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:01:05 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/14 12:02:09 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	nc;

	nc = (unsigned char)c;
	while (*s)
	{
		if (*s == nc)
			return ((char *)s);
		s++;
	}
	if (nc == 0)
		return ((char *)s);
	return (NULL);
}
