/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 13:46:31 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/18 10:10:30 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_gnl_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	d = (char *)dst;
	s = (char *)src;
	i = 0;
	if (d != s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_gnl_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	s1len;
	size_t	s2len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_gnl_strdup(s2));
	if (!s2)
		return (ft_gnl_strdup(s1));
	s1len = ft_gnl_strlen(s1);
	s2len = ft_gnl_strlen(s2);
	new = malloc(s1len + s2len + 1);
	if (new == NULL)
		return (NULL);
	ft_gnl_memcpy(new, s1, s1len);
	ft_gnl_memcpy(new + s1len, s2, s2len);
	new[s1len + s2len] = '\0';
	return (new);
}

char	*ft_gnl_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc((ft_gnl_strlen(s1) + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_gnl_strchr(const char *s, int c)
{
	unsigned char	newc;

	newc = (unsigned char)c;
	if (!s)
		return (NULL);
	if (newc == '\0')
		return ((char *)s + ft_gnl_strlen(s));
	while (*s != '\0')
	{
		if ((unsigned char)*s == newc)
			return ((char *)s);
		s++;
	}
	return (0);
}
