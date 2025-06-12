/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:44:53 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/12 14:11:25 by raalifa          ###   ########.fr       */
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
	return (ft_strdup(eq + 1));
}

static void	ft_print_env(t_env *env_list, int export_flag)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (export_flag || current->flag)
		{
			if (current->value)
				printf("declare -x %s=%s\n", current->key, current->value);
			else
				printf("declare -x %s\n", current->key);
		}
		current = current->next;
	}
}

static void	ft_add_or_update_env(t_shell *shell, char *arg, int export_flag)
{
	char	*key;
	char	*value;
	t_env	*curr;

	key = ft_get_key(arg);
	if (!key)
		return ;
	value = ft_get_value(arg);
	curr = shell->env_list;
	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = value;
			curr->flag = export_flag;
			free(key);
			return ;
		}
		curr = curr->next;
	}
	new_env(shell, key, value, export_flag);
}

static int	ft_is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_shell *shell, int export_flag)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		ft_print_env(shell->env_list, export_flag);
		return (0);
	}
	while (args[i])
	{
		if (ft_is_valid_identifier(args[i]))
			ft_add_or_update_env(shell, args[i], export_flag);
		else
			return (handle_error(shell, args[1], ERROR_GENERIC,
					INVALID_IDENTIFIER), 1);
		i++;
	}
	return (0);
}
