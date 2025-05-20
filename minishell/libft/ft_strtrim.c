/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 20:44:36 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/14 12:03:04 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && ft_check(set, s1[i]))
		i++;
	while (len > i && ft_check(set, s1[len - 1]))
		len--;
	ptr = (char *)malloc(len - i + 1);
	if (!ptr)
		return (NULL);
	j = 0;
	while (i < len)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}
