/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:44:17 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/04 12:38:35 by hparveen         ###   ########.fr       */
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

void	implement_minishell(t_shell *shell)
{
	disable_echoctl();
	while (1)
	{
		signal_init();
		ft_clear(shell, 1);
		if (isatty(0))
			shell->prompt = readline("minishell$ ");
		else
			shell->prompt = ft_strdup("");
		if (!shell->prompt || prompt_is_big(shell))
			exit_function(shell);
		if (shell->prompt)
		{
			add_history(shell->prompt);
			if (ft_parsing(shell))
				continue ;
			free(shell->prompt);
			shell->prompt = NULL;
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
	ft_clear_envlist(&shell.env_list);
	enable_echoctl();
	return (0);
}
