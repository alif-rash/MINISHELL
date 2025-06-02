
#include "../minishell.h"

void	ft_perror(char *cmd, char *msg)
{
	if (cmd && msg)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (cmd)
	{
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": Unknown error occurred\n", 2);
	}
}