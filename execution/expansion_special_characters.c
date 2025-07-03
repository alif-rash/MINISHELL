/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_special_characters.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 12:08:04 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 13:16:33 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Get home directory or PWD/OLDPWD for tilde expansion
 * @param shell Shell structure for environment access
 * @param input Input string
 * @param skip_len Pointer to skip length for special cases
 * @return Home directory path or NULL
 */
static char	*get_home(t_shell *shell, char *input, int *skip_len)
{
	char	*home;

	home = NULL;
	if ((input[1] == '+' || input[1] == '-') && (input[2] == '\0'
			|| input[2] == '/'))
	{
		if (input[1] == '+')
			home = search_in_env(shell, "PWD");
		else
			home = search_in_env(shell, "OLDPWD");
		(*skip_len)++;
	}
	else
		home = search_in_env(shell, "HOME");
	return (home);
}

/**
 * @brief Extract suffix after tilde expansion
 * @param input Input string
 * @param pos Position array [current, start]
 * @param skip_len Length to skip
 * @return Suffix string after tilde
 */
static char	*suffix_after_tilda(char *input, int pos[2], int skip_len)
{
	char	*suffix;

	suffix = NULL;
	while (input[pos[0]] && input[pos[0]] != '\'' && input[pos[0]] != '\"'
		&& input[pos[0]] != '$')
		pos[0]++;
	suffix = ft_substr(input, skip_len, pos[0] - skip_len);
	if (!suffix)
		suffix = ft_strdup("");
	return (suffix);
}

/**
 * @brief Search for user directory in tilde expansion
 * @param input Input string
 * @param pos Position array [current, start]
 * @param result Current result string
 * @return User directory path or original substring if not found
 */
static char	*search_user(char *input, int pos[2], char *result)
{
	char	*user;
	char	*path;

	user = NULL;
	path = NULL;
	user = get_username(input, pos);
	if (user)
	{
		path = ft_strjoin("/Users", user);
		if (access(path, F_OK) == -1)
		{
			free(path);
			free(user);
			free(result);
			return (ft_substr(input, 0, pos[0]));
		}
	}
	free(result);
	free(user);
	return (path);
}

char	*handle_tilda(char *input, int pos[2], char *result, t_shell *shell)
{
	char	*home;
	char	*suffix;
	int		skip_len;

	skip_len = 1;
	if (input[0] == '~' && (ft_strlen(input) == 1 || (input[1]
				&& (input[1] == '/' || input[1] == '+' || input[1] == '-'))))
	{
		home = get_home(shell, input, &skip_len);
		if (home)
		{
			suffix = suffix_after_tilda(input, pos, skip_len);
			free(result);
			result = ft_strjoin(home, suffix);
			free(suffix);
			return (result);
		}
	}
	else if (input[0] == '~' && (input[1] && ft_isalnum(input[1])))
		return (search_user(input, pos, result));
	pos[0]++;
	if (pos[1] < pos[0])
		return (append_data(input, pos, result, 0));
	free(result);
	return (ft_strdup("~"));
}

char	*expand_special_characters(char *input, int pos[2], char *result,
		t_shell *shell)
{
	if (input[pos[0]] == '~')
	{
		result = handle_tilda(input, pos, result, shell);
		pos[1] = pos[0];
	}
	else if (input[pos[0]] == '$')
	{
		result = handle_variable(input, pos, result, shell);
		pos[1] = pos[0];
	}
	else
		pos[0]++;
	return (result);
}
