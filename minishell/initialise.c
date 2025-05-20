#include "minishell.h"

t_env *envlst_new(char *env_variable, int flag)
{
    t_env *env_node;
    int i;

    if(!env_variable)
        return(NULL);
    env_node = malloc(sizeof(t_env));
    if(!env_node)
        return(NULL);
    env_node->env = NULL;
    env_node->key =NULL;
    env_node->value =  NULL;
    i = 0;
    env_node->env = ft_strdup(env_variable);
    if(!env_node->env)
    {
        free(env_node);
        return(NULL);
    }
    if(parse_key_value(env_variable, flag, &env_node, &i))
    {
        free_function((void **)&env_node->env, (void **)&env_node, NULL, NULL);
        return(NULL);
    }
    return(env_node);
}

void add_env_to_list(t_shell *shell)
{
    t_env *new_env_node;
    int i;
    int env_len;

    env_len = 0;
    new_env_node = NULL;
    if(!shell->env_array || !(*(shell->env_array)))
        return;
    env_len = ft_array_len(shell->env_array);
    shell->env_list = envlst_new(shell->env_array[0], 1);
    if(!shell->env_list)
        return;
    i = 1;
    while(i < env_len)
    {
        new_env_node = envlst_new(shell->env_array[i], 1);
        if(!new_env_node)
            return;
        env_lstadd_back(&shell->env_list, new_env_node);
        i++;
    }
}

char **create_new_env(void)
{
    char **env;
    char buffer[1024];

    env = malloc(sizeof(char *) * 4);
    if(!env)
    {
        perror("Malloc failed in creating non existing env");
        exit(EXIT_FAILURE);
    }
    if(getcwd(buffer, sizeof(buffer)) == NULL)
    {
        free(env);
        perror("getcwd failed in creating non existing env");
        return(NULL);
    }
    env[0] = ft_strjoin("PWD=", buffer);
    env[1] = ft_strdup("SHLVL=1");
    env[2] = ft_strdup("OLDPWD=");
    env[3] = NULL;
    return(env);
}

char **create_env(char **envp)
{
    int i;
    int env_len;
    char **env_array;

    if(!envp || !(*envp))
        return(NULL);
    env_len = ft_array_len(envp);
    env_array = malloc(sizeof(char *) * (env_len + 1));
    if(!env_array)
        return(NULL);
    i = 0;
    while(envp[i])
    {
        env_array[i] = ft_strdup(envp[i]);
        if(!env_array[i])
        {
            while(--i >= 0)
                free(env_array[i]);
            free(env_array);
            return(NULL);
        }
        i++;
    }
    env_array[i] = NULL;
    return(env_array);
}

void init(t_shell *shell, char **envp)
{
    shell->buffer = NULL;
    shell->env_array = create_env(envp);
    shell->env_list = NULL;
    if(!shell->env_array)
    {
        shell->env_array = create_new_env();
        add_env_to_list(shell);
    }
    else if(shell->env_array)
        add_env_to_list(shell);
    init_pwd_oldpwd(shell);
    update_shlvl(shell);
}
