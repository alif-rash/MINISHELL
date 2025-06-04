/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 08:15:55 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/04 09:24:19 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_accumulate(int fd, char *buffer, char *backup)
{
	int		read_line;
	char	*temp;

	read_line = 1;
	while (read_line > 0)
	{
		read_line = read(fd, buffer, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buffer[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (!backup)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (backup);
}

static char	*ft_extract(char *line)
{
	char	*backup;
	int		count;

	if (!line)
		return (NULL);
	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[count + 1] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count - 1);
	if (*backup == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = read_accumulate(fd, buffer, backup);
	free(buffer);
	buffer = NULL;
	if (!line)
	{
		free(backup);
		backup = NULL;
		return (NULL);
	}
	backup = ft_extract(line);
	return (line);
}
