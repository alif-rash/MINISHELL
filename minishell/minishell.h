/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:33:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/05/24 15:50:52 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

void				rl_replace_line(const char *text, int clear_undo);

# define ERROR_GENERIC 0
# define ERROR_PERROR 1
# define ERROR_SYNTAX 2

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_OPERATOR,
	T_BRACKETS,
	T_ALNUM,
	T_QUOTE,
	T_OP,
	T_REDIRECT_IN,
	T_REDIRECT_OUT,
	T_APPEND,
	T_HEREDOC,
	T_LOGICAND,
	T_LOGICOR,
	T_BRACKET,
	T_EOF,
	T_SPACE
}					t_token_type;

typedef struct s_token
{
	int				type;
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
	char			*prompt;
	int				index;
	t_token			*token_list;
}					t_shell;

void				check_args(int ac, char **av);
void				implement_minishell(t_shell *shell);
int					tokenisation(t_shell *shell, char *str);
int					is_token(int c, t_token_type token);
t_token				*token_operators(char *str, t_shell *shell, int index);
t_token				*token_brackets(char *str, t_shell *shell, int index);
t_token				*token_word(char *str, t_shell *shell, int index);
int					check_operator_type(int is_double, char current);
int					brackets_closed(char *str, t_shell *shell, int *start,
						int *end);
t_token				*create_token(t_shell *shell, int index, int type,
						char *str);
void				token_add_back(t_token **list, t_token *new);
t_token				*ft_token_last(t_token *list);
void				ft_free_tokenlist(t_token **token_list);

int					ft_parsing(t_shell *shell);

void				init(t_shell *shell, char **envp);
char				**create_env_array(char **envp);
char				**create_new_env_array(void);
t_env				*envlst_new(char *env_variable, int flag);
void				add_env_to_list(t_shell *shell, int flag);
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

int					ft_isspace(int c);
int					ft_isoperator(int c);
void				skip_spaces(char **str, int *i, int *sign);

void				free_function(void **a, void **b, void **c, void **d);
int					ft_array_len(char **array);
void				exit_function(t_shell *shell);

void				signal_init(void);
void				handle_signal(int signal);
void				disable_echoctl(void);
void				enable_echoctl(void);
int					exit_status(char *str, int status);

void				handle_error(t_shell *shell, char *msg, int error_type,
						int quote_flag);
void				ft_print_error(char *args, int flag, int fd);

#endif