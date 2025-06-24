/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:44:53 by raalifa           #+#    #+#             */
/*   Updated: 2025/06/19 16:51:52 by raalifa          ###   ########.fr       */
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

static void	ft_print_env(t_env *env_list)
{
	t_env	*current;
	char	*trimmed;

	current = env_list;
	while (current)
	{
		if (current->value && current->value[0] != '\0')
		{
			trimmed = ft_strtrim(current->value, "\"");
			printf("declare -x %s=\"%s\"\n", current->key, trimmed);
			free(trimmed);
		}
		else if (ft_strcmp(current->key, "OLDPWD") == 0)
			printf("declare -x %s\n", current->key);
		else if (current->flag == 1)
			printf("declare -x %s=\"\"\n", current->key);
		else
			printf("declare -x %s\n", current->key);
		current = current->next;
	}
}

static void	ft_process_env_key(t_shell *shell, char *key, char *value, int has_equal)
{
    t_env	*curr;

    curr = shell->env_list;
    while (curr)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (has_equal)
            {
                if (curr->value)
                    free(curr->value);
                curr->value = value;
                curr->flag = 0;
            }
            else
                curr->flag = 1;
            free(key);
            return ;
        }
        curr = curr->next;
    }
    new_env(shell, key, value, has_equal);
}

static void	ft_add_or_update_env(t_shell *shell, char *arg)
{
	char	*key;
	char	*value;
	int		has_equal;

	key = ft_get_key(arg);
	if (!key)
		return ;
	if (ft_strchr(arg, '=') != NULL)
	{
		value = ft_get_value(arg);
		has_equal = 1;
	}
	else
	{
		value = NULL;
		has_equal = 0;
	}
	ft_process_env_key(shell, key, value, has_equal);
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

int	ft_export(char **args, t_shell *shell)
{
	int	i;

	i = 1;
	if (!args[1])
	{
		ft_print_env(shell->env_list);
		return (0);
	}
	while (args[i])
	{
		if (ft_is_valid_identifier(args[i]))
			ft_add_or_update_env(shell, args[i]);
		else
			return (handle_error(shell, args[i], ERROR_GENERIC,
					INVALID_IDENTIFIER_E), 1);
		i++;
	}
	return (0);
}
