/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:44:17 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/19 13:22:31 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_args(int ac, char **av)
{
	if (ac != 1)
	{
		printf("minishell: %s: No such file or directory\n", av[1]);
		exit(127);
	}
}

/**
 * @brief Read user input line and handle prompt setting
 * @param shell Shell structure
 * @param is_interactive Whether shell is in interactive mode
 * @return 1 if line was read successfully, 0 otherwise
 */
static int	read_line_and_set_prompt(t_shell *shell, int is_interactive)
{
	char	*line;
	char	*temp;

	if (is_interactive)
		line = readline("minishell$ ");
	else
		line = get_next_line(0);
	if (!line)
	{
		if (is_interactive)
			ft_putendl_fd("exit", 1);
		ft_clear(shell, 2);
		exit(exit_status("exit status", -1));
	}
	if (!is_interactive)
	{
		temp = line;
		line = ft_strtrim(line, "\n");
		free(temp);
	}
	shell->prompt = line;
	return (0);
}

/**
 * @brief Handle prompt reading and command execution loop
 * @param shell Shell structure
 * @param is_interactive Whether shell is in interactive mode
 */
static void	handle_prompt_and_execute(t_shell *shell, int is_interactive)
{
	if (prompt_is_big(shell))
	{
		free(shell->prompt);
		shell->prompt = NULL;
		ft_clear(shell, 2);
		exit(exit_status("exit status", -1));
	}
	if (shell->prompt)
	{
		if (is_interactive)
			add_history(shell->prompt);
		if (ft_parsing(shell))
		{
			close_fds(shell);
			return ;
		}
		free(shell->prompt);
		shell->prompt = NULL;
		execute(shell, shell->ast);
		close_fds(shell);
	}
}

void	implement_minishell(t_shell *shell)
{
	int	is_interactive;

	if (isatty(0))
		enable_echoctl();
	disable_echoctl();
	while (1)
	{
		is_interactive = isatty(0);
		ft_dup(shell);
		signal_init();
		ft_clear(shell, 1);
		read_line_and_set_prompt(shell, is_interactive);
		handle_prompt_and_execute(shell, is_interactive);
		if (shell->heredoc_failed)
		{
			close_fds(shell);
			if (is_interactive)
				write(1, "\n", 1);
			shell->heredoc_failed = 0;
			continue ;
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	check_args(ac, av);
	init(&shell, envp);
	implement_minishell(&shell);
	ft_clear(&shell, 2);
	ft_free_envlist(&shell.env_list);
	if (isatty(0))
		enable_echoctl();
}
