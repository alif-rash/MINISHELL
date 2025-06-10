/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:13:16 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/10 09:53:55 by hparveen         ###   ########.fr       */
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
}

static void	print_after_args(int flag, int fd)
{
	if (flag == NO_DIR)
		ft_putstr_fd(": no such file or directory", fd);
	if (flag == NOT_FOUND)
		ft_putstr_fd(": command not found", fd);
	if (flag != IGNORE)
		ft_putchar_fd('\n', fd);
}

void	ft_print_error(char *args, int flag, int fd)
{
	(void)flag;
	ft_putstr_fd("minishell: ", fd);
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
	return (0);
}
