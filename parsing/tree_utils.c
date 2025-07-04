/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 08:19:14 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/12 09:23:13 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Free individual tree node and its resources
 * @param branch Tree node to free
 */
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

void	ft_clear_subtree(t_subtree **subtree)
{
	t_subtree	*current;
	t_subtree	*temp;

	if (!subtree || !*subtree)
		return ;
	current = *subtree;
	while (current)
	{
		temp = current->next;
		ft_free_treelist(current->tree);
		free(current);
		current = temp;
	}
	*subtree = NULL;
}
