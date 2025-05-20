/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:03:19 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/14 12:02:54 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	char	*h;
	char	*n;

	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		h = (char *)(haystack + i);
		n = (char *)needle;
		while (*h && *n && (*h == *n) && (i + (n - needle)) < len)
		{
			h++;
			n++;
		}
		if (*n == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
