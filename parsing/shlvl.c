/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:07 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/25 12:17:11 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	shlvl_overflow(int sign, unsigned long long number)
{
	if ((sign == 1 && number > 999))
		return (1);
	return (0);
}

static char	*shlvl_str(int sign, unsigned long long number)
{
	char	*str;
	char	*temp;

	str = ft_itoa(sign * (int)number);
	temp = add_quote(str);
	free(str);
	return (temp);
}

char	*ft_return_shlvl(char *value)
{
	int					index;
	int					sign;
	unsigned long long	number;

	index = 0;
	sign = 1;
	number = 0;
	skip_spaces(&value, &index, &sign);
	while (value[index])
	{
		if (ft_isdigit(value[index]))
			number = number * 10 + (value[index] - '0');
		else
			return (ft_strdup("\"1\""));
		if (shlvl_overflow(sign, number))
			return (ft_strdup("\"1\""));
		index++;
	}
	if (sign == -1)
		return (ft_strdup("\"0\""));
	if (sign == 1 && number == 999)
		return (ft_strdup("\"\""));
	number++;
	return (shlvl_str(sign, number));
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
