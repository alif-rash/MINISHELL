/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:10:19 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/27 12:43:54 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(t_shell *shell, char *key, char *value, int export_flag)
{
	char	*env_str;
	char	*key_with_equal;

	env_str = NULL;
	key_with_equal = NULL;
	if (export_flag)
		key_with_equal = ft_strjoin(key, "=");
	else
		key_with_equal = ft_strdup(key);
	if (export_flag)
	{
		if (value)
			env_str = ft_strjoin(key_with_equal, value);
		else
			env_str = ft_strdup(key_with_equal);
	}
	else
		env_str = ft_strdup(key_with_equal);
	if (value)
		free(value);
	free(key);
	free(key_with_equal);
	env_lstadd_back(&shell->env_list, envlst_new(env_str, export_flag));
	free(env_str);
}

void	add_env_to_list(t_shell *shell, int flag)
{
	t_env	*new_env_node;
	int		i;
	int		env_len;

	env_len = 0;
	new_env_node = NULL;
	if (!shell->env_array || !(*(shell->env_array)))
		return ;
	env_len = ft_array_len(shell->env_array);
	shell->env_list = envlst_new(shell->env_array[0], 1);
	if (!shell->env_list)
		return ;
	i = 1;
	while (i < env_len)
	{
		if (!flag && i == 2)
			new_env_node = envlst_new(shell->env_array[i], 0);
		else
			new_env_node = envlst_new(shell->env_array[i], 1);
		if (!new_env_node)
			return ;
		env_lstadd_back(&shell->env_list, new_env_node);
		i++;
	}
}

char	**create_new_env_array(void)
{
	char	**env;
	char	buffer[1024];

	env = malloc(sizeof(char *) * 4);
	if (!env)
	{
		perror("Malloc failed in creating non existing env");
		exit(EXIT_FAILURE);
	}
	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		free(env);
		perror("getcwd failed in creating non existing env");
		return (NULL);
	}
	env[0] = ft_strjoin("PWD=", buffer);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("OLDPWD=");
	env[3] = NULL;
	return (env);
}

char	**create_env_array(char **envp)
{
	int		i;
	int		env_len;
	char	**env_array;

	if (!envp || !(*envp))
		return (NULL);
	env_len = ft_array_len(envp);
	env_array = malloc(sizeof(char *) * (env_len + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_array[i] = ft_strdup(envp[i]);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	init(t_shell *shell, char **envp)
{
	shell->prompt = NULL;
	shell->env_array = create_env_array(envp);
	shell->env_list = NULL;
	shell->token_list = NULL;
	shell->index = 0;
	if (!shell->env_array)
	{
		shell->env_array = create_new_env_array();
		add_env_to_list(shell, 0);
	}
	else if (shell->env_array)
		add_env_to_list(shell, 1);
	init_pwd_oldpwd(shell);
	update_shlvl(shell);
}
