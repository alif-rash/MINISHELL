/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:34:12 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 11:48:12 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *command, t_shell *shell, int *error_flag)
{
	char	**path_dirs;
	char	*full_path;
	char	*temp_path;
	int		i;

	if (*command == '\0')
		return (NULL);
	path_dirs = ft_split(search_in_env(shell, "PATH"), ':');
	if (!path_dirs)
		return (*error_flag = 1, NULL);
	i = 0;
	while (path_dirs[i])
	{
		temp_path = ft_strjoin(path_dirs[i], "/");
		full_path = ft_strjoin(temp_path, command);
		free(temp_path);
		if (access(full_path, F_OK) == 0)
		{
			ft_free_array(path_dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (ft_free_array(path_dirs), NULL);
}

static char	*resolve_command_path(t_shell *shell, char first_char,
		char *command, int *path_found)
{
	if (first_char != '/' && first_char != '.')
		return (find_path(command, shell, path_found));
	else
		return (command);
}

static int	run_binary(t_shell *shell, char *command, char **args)
{
	struct stat	file_info;
	char		*exec_path;
	int			path_found;

	if (command[0] == '.' && command[1] == '\0')
	{
		if (!args[1])
			return (handle_error(shell, args[0], ERROR_GENERIC, NEED_FILE), 2);
		if (args[1][0] == '\0' || is_all_space(args[1]))
			return (handle_error(shell, args[1], ERROR_GENERIC, NO_FILE), 1);
	}
	path_found = 0;
	exec_path = resolve_command_path(shell, command[0], args[0], &path_found);
	if (exec_path && access(exec_path, F_OK) == 0
		&& access(exec_path, X_OK) == -1)
		return (handle_error(shell, exec_path, ERROR_GENERIC, DENIED), 126);
	if (!exec_path || access(exec_path, X_OK) == -1)
		return (handle_exec_errors(shell, exec_path, args[0], path_found));
	update_env_array(shell, shell->env_list, ft_envlist_size(shell->env_list));
	execve(exec_path, args, shell->env_array);
	if (errno == ENOEXEC)
		return (handle_noexec(shell, exec_path, args[0]));
	if (exec_path && !stat(exec_path, &file_info) && S_ISDIR(file_info.st_mode))
		return (handle_error(shell, exec_path, ERROR_GENERIC, IS_DIR), 126);
	return (1);
}

static void	child_process(t_shell *shell, t_tree *tree)
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
	signals_and_exitstatus(status);
}
