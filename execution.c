#include "minishell.h"

void execute(t_shell *shell, t_tree *tree)
{
    if(!shell->ast || !tree)
        return;
    if(tree->type == T_LOGICAND)
    {
        execute(shell, tree->lhs);
        if(exit_status("exit status", -1) == 0)
            execution(shell, tree->rhs);
    }
    else if(tree->type == T_LOGICOR)
    {
        execute(shell, tree->lhs);
        if(exit_status("exit status", -1) == 0)
            execution(shell, tree->rhs);
    }
    else if(tree->type == T_PIPE)
        execute_pipe(shell, tree);
}
