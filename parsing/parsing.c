/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:39:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 10:33:08 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * @brief Clear parsing data and return error status
 * @param shell Shell structure to clean up
 * @return Always returns 1 (error status)
 */
static int	ft_clear_and_exit(t_shell *shell)
{
	ft_free_tokenlist(&shell->token_list);
	shell->token_list = NULL;
	shell->ast = NULL;
	return (1);
}

int	ft_parsing(t_shell *shell)
{
	t_token	*tokens;

	shell->index = 0;
	if (tokenisation(shell, shell->prompt) || !shell->token_list)
	{
		free(shell->prompt);
		shell->prompt = NULL;
		return (1);
	}
	free(shell->prompt);
	shell->prompt = NULL;
	if (categorise_tokens(shell))
		return (1);
	if (check_syntax(shell))
		return (1);
	tokens = shell->token_list;
	heredoc(shell, tokens);
	if (shell->heredoc_failed == 1)
		return (ft_clear_and_exit(shell));
	shell->ast = build_ast(&tokens);
	if (shell->ast == NULL)
		return (handle_error(shell, "tree_create", ERROR_SYNTAX, '\0'), 1);
	ft_free_tokenlist(&shell->token_list);
	return (0);
}
