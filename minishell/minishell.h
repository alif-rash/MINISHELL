/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:33:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/20 13:15:22 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				fd;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*env;
	char			*key;
	char			*value;
	struct s_env	*next;
	int				flag;
}					t_env;

typedef struct s_shell
{
	t_env			*env_list;
	char			**env_array;
	char			*buffer;

}					t_shell;

void				check_args(int ac, char **av);

void				init(t_shell *shell, char **envp);
char				**create_env(char **envp);
char				**create_new_env(void);
t_env				*envlst_new(char *env_variable, int flag);
void				add_env_to_list(t_shell *shell);
int					parse_key_value(char *env_variable, int flag,
						t_env **env_node, int *index);
char				*add_quote(char *str);
int					assign_value(t_env **env_node, char *env_variable,
						int *start_index);
void				env_lstadd_back(t_env **env_list, t_env *new_node);
void				init_pwd_oldpwd(t_shell *shell);

char				*search_in_env(t_shell *shell, char *key);
void				new_env(t_shell *shell, char *key, char *value,
						int export_flag);
void				update_shlvl(t_shell *shell);
char				*shlvl_value(char *value);
char				*ft_return_shlvl(char *value);
void				skip_spaces(char **str, int *i, int *sign);

void				free_function(void **a, void **b, void **c, void **d);
int					ft_array_len(char **array);

#endif