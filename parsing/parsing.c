/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:39:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 10:08:31 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	shell->ast = build_ast(&tokens);
	print_ast(shell->ast, 0);
	if (shell->ast == NULL)
		return (handle_error(shell, "tree_create", ERROR_SYNTAX, '\0'), 1);
	ft_free_tokenlist(&shell->token_list);
	return (0);
}
