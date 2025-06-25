/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:13:16 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/25 10:18:57 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_error(t_shell *shell, char *msg, int error_type, int quote_flag)
{
	(void)shell;
	if (error_type == ERROR_GENERIC)
	{
		exit_status("exit status", 1);
		ft_print_error(msg, quote_flag, 2);
	}
	else if (error_type == ERROR_PERROR)
		perror("minishell$");
	else if (error_type == ERROR_SYNTAX)
	{
		exit_status("exit status", 258);
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("'\n", 2);
	}
	else if (error_type == ERROR_NUMERIC)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

static void	print_helper(int flag, int fd)
{
	if (flag == INVALID_IDENTIFIER || flag == INVALID_IDENTIFIER_E)
		ft_putstr_fd("': not a valid identifier", fd);
	if (flag == NEED_FILE)
	{
		ft_putstr_fd(": filename argument required\n", fd);
		ft_putstr_fd(".: usage: . filename [arguments]", fd);
	}
	if (flag != IGNORE)
		ft_putchar_fd('\n', fd);
}

static void	print_after_args(int flag, int fd)
{
	if (flag == ERR_AMBIGOUS_REDIRECT)
		ft_putstr_fd(": ambiguous redirect", fd);
	if (flag == NO_DIR || flag == NO_DIR_CD || flag == ENV_NO_FILE
		|| flag == NO_FILE)
		ft_putstr_fd(": No such file or directory", fd);
	if (flag == NOT_FOUND)
		ft_putstr_fd(": command not found", fd);
	if (flag == NUM_REQUIRED)
		ft_putstr_fd(": numeric argument required", fd);
	if (flag == DENIED)
		ft_putstr_fd(": Permission denied", fd);
	if (flag == NO_HOME)
		ft_putstr_fd(": HOME not set", fd);
	if (flag == NO_OLDPWD)
		ft_putstr_fd(": OLDPWD not set", fd);
	if (flag == BAD_OPTION)
		ft_putstr_fd(": invalid option", fd);
	if (flag == IS_DIR)
		ft_putstr_fd(": is a directory", fd);
	print_helper(flag, fd);
}

void	ft_print_error(char *args, int flag, int fd)
{
	(void)flag;
	ft_putstr_fd("minishell: ", fd);
	if (flag == NUM_REQUIRED)
		ft_putstr_fd("exit: ", fd);
	if (flag == NO_DIR_CD)
		ft_putstr_fd("cd: ", fd);
	if (flag == TOO_MANY_ARGS)
		ft_putstr_fd("exit: too many arguments", fd);
	if (flag == INVALID_IDENTIFIER_E)
		ft_putstr_fd("export: `", fd);
	if (flag == INVALID_IDENTIFIER)
		ft_putstr_fd("unset: `", fd);
	if (args)
		ft_putstr_fd(args, fd);
	print_after_args(flag, fd);
}

int	print_error(t_shell *shell, int error_code, t_token *current)
{
	if (error_code == ERR_OP_SYNTAX || error_code == ERR_OP_START)
	{
		if (current->next && error_code != ERR_OP_START)
			return (handle_error(shell, current->next->value, ERROR_SYNTAX,
					'\0'), 1);
		return (handle_error(shell, current->value, ERROR_SYNTAX, '\0'), 1);
	}
	if (error_code == ERR_REDIR_SYNTAX)
	{
		if (current->next && current->next->type == T_PIPE)
			return (handle_error(shell, current->next->value, ERROR_SYNTAX,
					'\0'), 1);
		return (handle_error(shell, current->next->value, ERROR_SYNTAX, '\0'),
			1);
	}
	if (error_code == ERR_DOUBLEBRACKET)
		return (handle_error(shell, "(", ERROR_SYNTAX, '\0'), 1);
	if (error_code == ERR_INVALIDSUBSHELL)
		return (handle_error(shell, current->next->value, ERROR_SYNTAX, '\0'),
			1);
	if (error_code == ERR_AMBIGOUS_REDIRECT)
		return (handle_error(shell, current->next->value, ERROR_GENERIC,
				ERR_AMBIGOUS_REDIRECT), 1);
	return (0);
}
