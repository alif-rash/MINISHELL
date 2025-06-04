/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 08:16:18 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/04 09:09:27 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in(t_tree *tree)
{
	int	file;

	file = 0;
	file = open(tree->file, O_RDONLY);
	if (file == -1)
	{
		printf("minishell: ");
		perror(tree->file);
		return (1);
	}
	if (dup2(file, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(file);
	return (0);
}

static int	redirect_out(t_tree *tree)
{
	int	file;

	file = 0;
	file = open(tree->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
	{
		printf("minishell: ");
		perror(tree->file);
		return (1);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(file);
	return (0);
}

static int	append(t_tree *tree)
{
	int	file;

	file = 0;
	file = open(tree->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file == -1)
	{
		printf("minishell: ");
		perror(tree->file);
		return (1);
	}
	if (dup2(file, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(file);
	return (0);
}

static int	setup_heredoc_input(int fd, t_tree *tree, t_shell *shell)
{
	int	temp_fd;

	if (fd != -1)
	{
		temp_fd = open(".heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		expand_heredoc_to_file(shell, fd, temp_fd, tree);
		close(temp_fd);
		close(fd);
		temp_fd = open(".heredoc_file", O_RDONLY, 0777);
		dup2(temp_fd, STDIN_FILENO);
		close(temp_fd);
		unlink(".heredoc_file");
		fd = -1;
		tree->fd = -1;
		return (0);
	}
	return (1);
}

void	execute_redirections(t_shell *shell, t_tree *tree)
{
	int	flag;

	flag = 0;
	if (!shell->ast || !tree)
		return ;
	if (tree->type == T_REDIRECT_IN)
		flag = redirect_in(tree);
	else if (tree->type == T_REDIRECT_OUT)
		flag = redirect_out(tree);
	else if (tree->type == T_APPEND)
		flag = append(tree);
	else if (tree->type == T_HEREDOC)
		flag = setup_heredoc_input(tree->fd, tree, shell);
	if (tree->lhs && flag == 0)
		execute(shell, tree->lhs);
}
