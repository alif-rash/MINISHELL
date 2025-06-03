/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:57:48 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 09:28:48 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_function(void **a, void **b, void **c)
{
	if (a && *a)
	{
		free(*a);
		*a = NULL;
	}
	if (b && *b)
	{
		free(*b);
		*b = NULL;
	}
	if (c && *c)
	{
		free(*c);
		*c = NULL;
	}
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
	array = NULL;
}

void	ft_clear(t_shell *shell)
{
	if (shell->token_list)
		ft_free_tokenlist(&(shell->token_list));
	if (shell->env_array)
		ft_free_array(shell->env_array);
	if (shell->env_list)
		ft_free_envlist(&(shell->env_list));
	if (shell->ast)
		ft_free_treelist(shell->ast);
	shell->token_list = NULL;
	shell->ast = NULL;
}
