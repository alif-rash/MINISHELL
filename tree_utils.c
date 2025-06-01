#include "minishell.h"

static void ft_free_treenode(t_tree *branch)
{
    if(!branch)
        return;
    if(branch->file)
    {
        free(branch->file);
        branch->file = NULL;
    }
    if(branch->fd >= 0)
    {
        close(branch->fd);
        branch->fd = -1;
    }
    free(branch);
}

void ft_free_treelist(t_tree *branch)
{
    int i;
    
    if(!branch)
        return;
    ft_clear_branch(branch->lhs);
    ft_clear_branch(branch->rhs);
    if(branch->args)
    {
        i = 0;
        while(branch->args[i])
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
