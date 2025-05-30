/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 09:51:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/28 10:30:50 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_word(char *str, t_shell *shell, int index)
{
	char	quote;

	while (str[shell->index])
	{
		while (str[shell->index] && ft_isspace(str[shell->index]) == 0
			&& str[shell->index] != '\'' && str[shell->index] != '\"'
			&& ft_isoperator(str[shell->index]) == 0 && str[shell->index] != '('
			&& str[shell->index] != ')')
			shell->index++;
		if ((str[shell->index] && (ft_isoperator(str[shell->index]) == 1
					|| ft_isspace(str[shell->index]) == 1
					|| str[shell->index] == '(' || str[shell->index] == ')'))
			|| str[shell->index] == '\0')
			break ;
		quote = str[shell->index];
		shell->index++;
		while (str[shell->index] && str[shell->index] != quote)
			shell->index++;
		if (str[shell->index] && str[shell->index] == quote)
			shell->index++;
		else
			return (handle_error(shell, "newline", ERROR_SYNTAX, '\0'), NULL);
	}
	index = shell->index - index;
	return (create_token(shell, index, T_WORD, str));
}

t_token	*token_brackets(char *str, t_shell *shell, int index)
{
	int	type;
	int	start_index;
	int	end_index;

	type = T_BRACKET;
	if (!brackets_closed(str, shell, &start_index, &end_index))
	{
		handle_error(shell, "new line", ERROR_SYNTAX, '\0');
		return (NULL);
	}
	index = shell->index - index;
	return (create_token(shell, index, type, str));
}

t_token	*token_operators(char *str, t_shell *shell, int index)
{
	int		is_double;
	int		type;
	char	current;

	is_double = 0;
	current = str[shell->index];
	shell->index++;
	if (str[shell->index] == current)
	{
		shell->index++;
		is_double = 1;
	}
	if (current == '&' && !is_double)
		return (handle_error(shell, "&", ERROR_SYNTAX, '\0'), NULL);
	type = check_operator_type(is_double, current);
	index = shell->index - index;
	return (create_token(shell, index, type, str));
}

int	is_token(int c, t_token_type token)
{
	if (token == T_ALNUM)
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z'));
	else if (token == T_SPACE)
		return (c == 32 || (c >= 9 && c <= 13));
	else if (token == T_QUOTE)
		return (c == '\'' || c == '\"');
	else if (token == T_OP)
		return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
	else if (token == T_OPERATOR)
		return (c == '|' || c == '<' || c == '>' || c == '&');
	else if (token == T_BRACKETS)
		return (c == '(' || c == ')');
	return (0);
}

int	tokenisation(t_shell *shell, char *str)
{
	int		start_index;
	t_token	*current;

	if (!str || !str[shell->index])
		return (1);
	while (str[shell->index])
	{
		start_index = shell->index;
		if (is_token(str[shell->index], T_SPACE))
		{
			while (str[shell->index] && is_token(str[shell->index], T_SPACE))
				shell->index++;
			continue ;
		}
		else if (is_token(str[shell->index], T_OPERATOR))
			current = token_operators(str, shell, start_index);
		else if (is_token(str[shell->index], T_BRACKETS))
			current = token_brackets(str, shell, start_index);
		else
			current = token_word(str, shell, start_index);
		if (!current)
			return (1);
		token_add_back(&shell->token_list, current);
	}
	return (0);
}
