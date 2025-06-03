/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:33:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/03 10:37:13 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>

# ifndef ARG_MAX
#  define ARG_MAX 262144
# endif

# define ERROR_GENERIC 0
# define ERROR_PERROR 1
# define ERROR_SYNTAX 2
# define ERROR_MALLOC 3
# define ERR_OP_SYNTAX 101
# define ERR_OP_START 102
# define ERR_REDIR_SYNTAX 103
# define ERR_DOUBLEBRACKET 104
# define ERR_INVALIDSUBSHELL 105

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,
	T_OPERATOR,
	T_BRACKETS,
	T_ALNUM,
	T_QUOTE,
	T_OP,
	T_COMMAND,
	T_ARGUMENT,
	T_FILENAME,
	T_DELIMITER,
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

typedef struct s_tree
{
	int				type;
	int				fd;
	char			*file;
	char			**args;
	struct s_tree	*lhs;
	struct s_tree	*rhs;
}					t_tree;

typedef struct s_shell
{
	t_env			*env_list;
	char			**env_array;
	char			*prompt;
	int				index;
	t_token			*token_list;
	t_tree			*ast;
}					t_shell;

/**
 * @brief Replaces the current line in the readline buffer with the specified text.
 * @param text The new text to replace the current line. Must be a null-terminated string.
 * @param clear_undo If non-zero, the undo information for the current line is cleared.
 */
void				rl_replace_line(const char *text, int clear_undo);
void				check_args(int ac, char **av);
int					prompt_is_big(t_shell *shell);
void				implement_minishell(t_shell *shell);
int					tokenisation(t_shell *shell, char *str);
int					is_token(int c, t_token_type token);
t_token				*token_operators(char *str, t_shell *shell, int index);
t_token				*token_brackets(char *str, t_shell *shell, int index);
t_token				*token_word(char *str, t_shell *shell, int index);
int					check_operator_type(int is_double, char current);
int					brackets_closed(char *str, t_shell *shell, int *start,
						int *end);
int					check_nesting(const char *s);
t_token				*create_token(t_shell *shell, int index, int type,
						char *str);
int					categorise_tokens(t_shell *shell);
void				token_add_back(t_token **list, t_token *new);
t_token				*ft_token_last(t_token *list);
void				ft_free_tokenlist(t_token **token_list);

int					ft_parsing(t_shell *shell);
int					check_syntax(t_shell *shell);
int					syntax_check_brackets(t_token *current, t_token *prev);
int					syntax_check_redirections(t_token *current);
int					syntax_check_operators(t_token *current, int index);

void				init(t_shell *shell, char **envp);
char				**create_env_array(char **envp);
char				**create_new_env_array(void);
t_env				*envlst_new(char *env_variable, int flag);
void				add_env_to_list(t_shell *shell, int flag);
int					parse_key_value(char *env_variable, int flag,
						t_env **env_node, int *index);
char				*add_quote(char *str);
char				*remove_quotes(char *str);
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

t_tree				*build_ast(t_token **tokens);
t_tree				*build_ast_and(t_token **tokens);
t_tree				*build_ast_or(t_token **tokens);
t_tree				*build_ast_pipe(t_token **tokens);
t_tree				*build_ast_redirections(t_token **tokens);
t_tree				*build_ast_command(t_token **tokens);

void				heredoc(t_shell *shell, t_token *tokens);
int					multiple_heredocs(t_token *list);

int					ft_isspace(int c);
int					is_all_space(const char *s);
int					ft_isoperator(int c);
void				skip_spaces(char **str, int *i, int *sign);

void				free_function(void **a, void **b, void **c);
void				ft_free_array(char **array);
void				ft_free_envlist(t_env **env_list);
void				ft_clear(t_shell *shell);
int					ft_array_len(char **array);
void				exit_function(t_shell *shell);

void				signal_init(void);
void				handle_signal(int signal);
void				signal_heredoc(void);
void				handle_heredoc(int signal);
void				disable_echoctl(void);
void				enable_echoctl(void);
int					exit_status(char *str, int status);

void				handle_error(t_shell *shell, char *msg, int error_type,
						int quote_flag);
void				ft_print_error(char *args, int flag, int fd);
int					print_error(t_shell *shell, int error_code,
						t_token *current);

int					ft_echo(char **args);

void				ft_free_treelist(t_tree *branch);

#endif