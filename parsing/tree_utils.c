/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:19:14 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 08:19:19 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_treenode(t_tree *branch)
{
	if (!branch)
		return ;
	if (branch->file)
	{
		free(branch->file);
		branch->file = NULL;
	}
	if (branch->fd >= 0)
	{
		close(branch->fd);
		branch->fd = -1;
	}
	free(branch);
}

void	ft_free_treelist(t_tree *branch)
{
	int	i;

	if (!branch)
		return ;
	ft_free_treelist(branch->lhs);
	ft_free_treelist(branch->rhs);
	if (branch->args)
	{
		i = 0;
		while (branch->args[i])
		{
			free(branch->args[i]);
			branch->args[i] = NULL;
			i++;
		}
		free(branch->args);
		branch->args = NULL;
	}
	ft_free_treenode(branch);
}
