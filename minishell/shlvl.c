/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:07 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/26 09:14:31 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return_shlvl(char *value)
{
	int					index;
	int					sign;
	unsigned long long	number;

	index = 0;
	sign = 1;
	number = 0;
	skip_spaces(&value, &index, &sign);
	while (value[index] >= '0' && value[index] <= '9')
	{
		number = number * 10 + (value[index] - '0');
		if ((sign == 1 && number > 9223372036854775807ULL) || (sign == -1
				&& number > 9223372036854775808ULL))
			return (ft_strdup("1"));
		index++;
	}
	if (sign == 1 && number == 9223372036854775807ULL)
		return (ft_strdup("0"));
	number++;
	if ((sign == 1 && number > 9223372036854775807ULL) || (sign == -1
			&& number > 9223372036854775808ULL))
		return (ft_strdup("1"));
	return (add_quote(ft_itoa(sign * (int)number)));
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

static void	update_existing_value(t_env *env_node)
{
	char	*updated_value;
	char	*unquoted;

	env_node->flag = 1;
	if (env_node->value == NULL)
		env_node->value = ft_strdup("\"1\"");
	else
	{
		unquoted = remove_quotes(env_node->value);
		updated_value = shlvl_value(unquoted);
		free(unquoted);
		free(env_node->value);
		env_node->value = updated_value;
		free(updated_value);
	}
}

void	update_shlvl(t_shell *shell)
{
	t_env	*env_node;

	env_node = shell->env_list;
	while (env_node)
	{
		if (ft_strcmp(env_node->key, "SHLVL") == 0)
		{
			update_existing_value(env_node);
			break ;
		}
		env_node = env_node->next;
	}
	if (search_in_env(shell, "SHLVL") == NULL)
		new_env(shell, ft_strdup("SHLVL"), ft_strdup("\"1\""), 1);
}

char	*remove_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len >= 2 && str[0] == '"' && str[len - 1] == '"')
		return (ft_substr(str, 1, len - 2));
	return (ft_strdup(str));
}
