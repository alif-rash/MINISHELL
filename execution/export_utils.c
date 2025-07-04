/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 08:17:10 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/24 08:17:31 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_key(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (ft_strndup(arg, i));
}

char	*ft_get_value(const char *arg)
{
	const char	*eq = ft_strchr(arg, '=');

	if (!eq)
		return (NULL);
	if (*(eq + 1) == '\0')
		return (ft_strdup(""));
	else
		return (ft_strdup(eq + 1));
}
