/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:39:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/29 13:39:25 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parsing(t_shell *shell)
{
	t_token	*list;

	// t_token	*tokens;
	shell->index = 0;
	if (tokenisation(shell, shell->prompt) || !shell->token_list)
	{
		free(shell->prompt);
		shell->prompt = NULL;
		return (1);
	}
	if (categorise_tokens(shell))
		return (1);
	list = shell->token_list;
	while (list)
	{
		printf("Token: %-10s | Type: %d\n", list->value, list->type);
		list = list->next;
	}
	if (check_syntax(shell))
		return (1);
	// tokens = shell->token_list;
	// shell->ast = create_tree(&tokens);
	free(shell->prompt);
	shell->prompt = NULL;
	ft_free_tokenlist(&shell->token_list);
	return (0);
}
