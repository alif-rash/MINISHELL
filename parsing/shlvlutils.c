/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvlutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 08:03:47 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/02 16:59:47 by raalifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}

char	*shlvl_value(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (!((value[i] >= '0' && value[i] <= '9') || (value[0] == '-')
				|| (value[0] == '+')))
			return (ft_strdup("\"1\""));
		i++;
	}
	return (ft_return_shlvl(value));
}
