
#include "../minishell.h"

void ft_perror(char *msg)
{
    if (msg)
    {
        fprintf(stderr, "Error: %s\n", msg);
    }
    else
    {
        fprintf(stderr, "Error: Unknown error occurred\n");
    }
}