#include "minishell.h"

int multiple_heredocs(t_token *list)
{
    while(list)
    {
        if(list->type == T_LOGICAND || list->type == T_LOGICOR)
            return(0);
        if(list->type == T_HEREDOC)
            return(1);
        list = list->next;
    }
}
