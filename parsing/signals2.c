/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:13:26 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 08:13:30 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		exit_status("exit status", 1);
		close(STDIN_FILENO);
	}
}
