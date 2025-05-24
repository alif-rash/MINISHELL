/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:13:16 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/24 10:14:02 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(t_shell *shell, char *msg, int error_type, int quote_flag)
{
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
		ft_putchar_fd(msg, 2);
		ft_putchar_fd("'\n", 2);
	}
}

void	ft_print_error(char *msg, int flag, int fd)
{
}
