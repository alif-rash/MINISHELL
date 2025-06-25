/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:04:20 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/25 12:16:49 by hparveen         ###   ########.fr       */
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

int	ft_isnumeric(const char *str)
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

void	ft_tolower_str(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] >= 'A' && (*str)[i] <= 'Z')
			(*str)[i] += 32;
		i++;
	}
}

int	ft_envlist_size(t_env *env_list)
{
	int	size;

	size = 0;
	while (env_list)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}

char	*ft_strtrim_sides(char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
