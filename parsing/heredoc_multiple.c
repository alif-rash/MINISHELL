/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_multiple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:12:38 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 08:12:43 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	multiple_heredocs(t_token *list)
{
	while (list)
	{
		if (list->type == T_LOGICAND || list->type == T_LOGICOR)
			return (0);
		if (list->type == T_HEREDOC)
			return (1);
		list = list->next;
	}
	return (0);
}
