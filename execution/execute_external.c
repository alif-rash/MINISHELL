/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:34:12 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/09 20:52:42 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *command, t_shell *shell, int *path_found)
{
}

static char	*resolve_command_path(t_shell *shell, char first_char,
		char *command, int *path_found)
{
	if (first_char != '/' && first_char != '.')
		return (find_path(command, shell, path_found));
	else
		return (command);
}

int	run_binary(t_shell *shell, char *command, char **args)
{
	struct stat	file_info;
	char		*exec_path;
	int			path_found;

	path_found = 0;
	ft_tolower_str(&args[0]);
	exec_path = resolve_command_path(shell, command[0], args[0], &path_found);
	if (!exec_path || access(exec_path, X_OK) == -1)
	{
		if (!path_found && (command[0] == '/' || (command[0] == '.'
					&& command[1] == '/')))
			handle_error(shell, args[0], ERROR_GENERIC, 12);
		else
			handle_error(shell, args[0], ERROR_GENERIC, 14);
		return (127);
	}
}

void	child_process(t_shell *shell, t_tree *tree)
{
	int	exit_status;

	signal_dfl();
	exit_status = run_binary(shell, tree->args[0], tree->args);
	ft_clear(shell, 2);
	if (exit_status != 0)
		exit(exit_status);
}

void	external_execution(t_shell *shell, t_tree *tree)
{
	int		status;
	pid_t	pid;

	signal_heredoc();
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		ft_clear(shell, 2);
		return ;
	}
	else if (pid == 0)
		child_process(shell, tree);
	waitpid(pid, &status, 0);
	signal_init();
}
