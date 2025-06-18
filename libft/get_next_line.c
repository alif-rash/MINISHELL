/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:15:55 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/18 10:11:20 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_get_rest(char *str)
{
	char	*rest;
	int		i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	rest = ft_gnl_strdup(str + i);
	if (!rest)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (rest);
}

static char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*ft_readbuff(int fd, char *str, char *buffer)
{
	char	*temp;
	ssize_t	size;

	size = 1;
	if (str == NULL || buffer == NULL)
		return (NULL);
	while (size > 0 && (!ft_gnl_strchr(str, '\n')))
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == 0)
			return (free(buffer), str);
		if (size < 0)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[size] = '\0';
		temp = str;
		str = ft_gnl_strjoin(str, buffer);
		free(temp);
	}
	free(buffer);
	return (str);
}

static char	*ft_read(int fd, char *str)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (!str)
		str = ft_gnl_strdup("");
	if (!str)
	{
		free(buffer);
		return (NULL);
	}
	str = ft_readbuff(fd, str, buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd == -42)
		return (free(str), str = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
	{
		str = ft_gnl_strdup("");
		return (NULL);
	}
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line = ft_get_line(str);
	str = ft_get_rest(str);
	return (line);
}