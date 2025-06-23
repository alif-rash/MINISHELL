/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hparveen <hparveen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 09:33:06 by hparveen          #+#    #+#             */
/*   Updated: 2025/06/23 08:34:26 by hparveen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
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
# define ERROR_NUMERIC 255

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
}						t_token_type;

typedef enum e_error_flag
{
	NO_FILE = 0,
	NOT_IN_PWD = 1,
	AMBIGOUS_REDIRECT = 2,
	BAD_ID = 3,
	TOO_MANY_ARGS = 4,
	NUM_REQUIRED = 5,
	IS_DIR = 6,
	ENV_NO_FILE = 10,
	NO_HOME = 11,
	NO_DIR = 12,
	DENIED = 13,
	NOT_FOUND = 14,
	BAD_OPTION = 15,
	NO_OLDPWD = 16,
	NEED_FILE = 17,
	INVALID_IDENTIFIER = 18,
	IGNORE = 100
}						t_error_flag;

typedef struct s_token
{
	int					type;
	char				*value;
	int					fd;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*env;
	char				*key;
	char				*value;
	struct s_env		*next;
	int					flag;
}						t_env;

typedef struct s_tree
{
	int					type;
	int					fd;
	char				*file;
	char				**args;
	struct s_tree		*lhs;
	struct s_tree		*rhs;
}						t_tree;

typedef struct s_subtree
{
	t_tree				*tree;
	struct s_subtree	*next;
}						t_subtree;

typedef struct s_shell
{
	t_env				*env_list;
	char				**env_array;
	char				*prompt;
	int					index;
	int					stdin;
	int					stdout;
	int					heredoc_failed;
	t_token				*token_list;
	t_tree				*ast;
	t_subtree			*subtree;
}						t_shell;

/**

	* @brief Replaces the current line in the readline buffer
		with the specified text.

	* @param text The new text to replace the current line.
	Must be a null-terminated string.
 * @param clear_undo If non-zero,
	the undo information for the current line is cleared.
 */
void					rl_replace_line(const char *text, int clear_undo);

/**
 * @brief Validates the command-line arguments passed to the program.
 * @param ac The argument count.
 * @param av The argument vector containing the arguments.
 */
void					check_args(int ac, char **av);

/**
 * @brief Determines whether the prompt is big.
 *
 * @param shell A pointer to the shell structure containing relevant data.
 * @return int Returns 1 if the prompt is considered "big", otherwise 0.
 */
int						prompt_is_big(t_shell *shell);

/**
 * @brief Executes the main functionality of the minishell program.
 *
 * @param shell A pointer to the shell structure containing relevant data.
 */
void					implement_minishell(t_shell *shell);

/**
 * @brief

	* This function iterates through the input string
	and identifies tokens based on their type:
 * spaces, operators, brackets,
	or words. It creates corresponding token objects and appends them
 * to the shell's token list. If an error occurs during token creation,
	the function returns an error code.

	* @param shell A pointer to the shell structure containing 
	the token list and index.
 * @param str The input string to be tokenized.
 * @return Returns 0 on success, or 1 if an error occurs during tokenization.
 */
int						tokenisation(t_shell *shell, char *str);

/**
 * @brief Checks if a given character matches a specific token type.
 * @param c The character to be checked.
 * @param token The token type to compare against.
 * @return int Returns 1 if the character matches the token type, otherwise 0.
 */
int						is_token(int c, t_token_type token);

/**
 * @brief Processes operators in the input string and creates a token.
 *
 * @param str The input string to parse.
 * @param shell Pointer to the shell structure.
 * @param index The current index in the input string.
 * @return Pointer to the created token.
 */
t_token					*token_operators(char *str, t_shell *shell, int index);

/**
 * @brief Processes brackets in the input string and creates a token.
 *
 * @param str The input string to parse.
 * @param shell Pointer to the shell structure.
 * @param index The current index in the input string.
 * @return Pointer to the created token.
 */
t_token					*token_brackets(char *str, t_shell *shell, int index);

/**
 * @brief Processes words in the input string and creates a token.
 *
 * @param str The input string to parse.
 * @param shell Pointer to the shell structure.
 * @param index The current index in the input string.
 * @return Pointer to the created token.
 */
t_token					*token_word(char *str, t_shell *shell, int index);

/**
 * @brief Determines the type of operator based on its characteristics.
 *
 * @param is_double Indicates if the operator is a double character operator.
 * @param current The current character being processed.
 * @return Integer representing the operator type.
 */
int						check_operator_type(int is_double, char current);

/**
 * @brief Checks if brackets in the input string are properly closed.
 *
 * @param str The input string to parse.
 * @param shell Pointer to the shell structure.
 * @param start Pointer to the start index of the brackets.
 * @param end Pointer to the end index of the brackets.
 * @return Integer indicating whether the brackets are closed (1 for closed,
	0 for not).
 */
int						brackets_closed(char *str, t_shell *shell, int *start,
							int *end);

/**
 * @brief Checks the nesting level of brackets in the input string.
 *
 * @param s The input string to parse.
 * @return Integer indicating the nesting level.
 */
int						check_nesting(const char *s);

/**
 * @brief Creates a new token with the specified parameters.
 *
 * @param shell Pointer to the shell structure.
 * @param index The index of the token.
 * @param type The type of the token.
 * @param str The string value of the token.
 * @return Pointer to the created token.
 */
t_token					*create_token(t_shell *shell, int index, int type,
							char *str);

/**
 * @brief Categorizes tokens in the shell structure.
 *
 * @param shell Pointer to the shell structure.
 * @return Integer indicating success or failure.
 */
int						categorise_tokens(t_shell *shell);

/**
 * @brief Adds a new token to the end of the token list.
 *
 * @param list Pointer to the token list.
 * @param new Pointer to the new token to add.
 */
void					token_add_back(t_token **list, t_token *new);

/**
 * @brief Retrieves the last token in the token list.
 *
 * @param list Pointer to the token list.
 * @return Pointer to the last token in the list.
 */
t_token					*ft_token_last(t_token *list);

/**
 * @brief Frees the memory allocated for the token list.
 *
 * @param token_list Pointer to the token list to free.
 */
void					ft_free_tokenlist(t_token **token_list);

/**
 * @brief Parses the shell input and prepares the abstract syntax tree (AST).
 * This function performs the following steps:
 * - Tokenizes the shell input.
 * - Categorizes the tokens.
 * - Checks the syntax of the tokens.
 * - Handles heredoc functionality.
 * - Builds the abstract syntax tree (AST) from the tokens.
 * - Frees the token list after AST creation.

	* @param shell A pointer to the shell structure containing
	the input prompt and other data.
 * @return Returns 0 on success, or 1 on failure due to tokenization,
	syntax errors, or AST creation issues.
 */
int						ft_parsing(t_shell *shell);

/**
 * @brief Checks the syntax of the shell input for errors.
 *

	* @param shell Pointer to the shell structure 
	containing input and state information.
 * @return int Returns 0 if the syntax is valid, or an error code if invalid.
 */
int						check_syntax(t_shell *shell);

/**
 * @brief Validates the syntax of brackets in the shell input.
 *
 * @param current Pointer to the current token being analyzed.
 * @param prev Pointer to the previous token in the sequence.
 * @return int Returns 0 if the brackets syntax is valid,
	or an error code if invalid.
 */
int						syntax_check_brackets(t_token *current, t_token *prev);

/**
 * @brief Validates the syntax of redirection operators in the shell input.
 *
 * @param current Pointer to the current token being analyzed.
 * @return int Returns 0 if the redirection syntax is valid,
	or an error code if invalid.
 */
int						syntax_check_redirections(t_token *current);

/**
 * @brief Validates the syntax of operators in the shell input.
 *
 * @param current Pointer to the current token being analyzed.
 * @param index Index of the operator in the token sequence.
 * @return int Returns 0 if the operator syntax is valid,
	or an error code if invalid.
 */
int						syntax_check_operators(t_token *current, int index);

/**
 * @brief Initializes the shell structure and environment variables.
 *
 * @param shell Pointer to the shell structure to initialize.
 * @param envp Array of environment variables passed to the program.
 */
void					init(t_shell *shell, char **envp);

/**
 * @brief Copies the environment variables to an array.
 *
 * @param envp Array of environment variables passed to the program.
 * @return A newly allocated array of environment variables.
 */
char					**create_env_array(char **envp);

/**
 * @brief Creates a new environment variable array with default values.
 *
 * This function allocates memory for a new environment variable array and
 * initializes it with default values for `PWD`, `SHLVL`, and `OLDPWD`.
 * It uses the current working directory to set the `PWD` variable.
 *
 * @return A newly allocated array of environment variables.
 */
char					**create_new_env_array(void);

/**

	* @brief This function allocates memory for a 
	new `t_env` node and initializes its fields.

	* It duplicates the provided environment variable 
	string and parses its key-value pair
 * based on the given flag.
 * @param env_variable The environment variable string (key=value format).
 * @param flag Flag indicating specific behavior or properties of the node.
 * @return A pointer to the newly created environment variable node.
 */
t_env					*envlst_new(char *env_variable, int flag);

/**
 * @brief Adds environment variables to the shell's linked list.
 *
 * @param shell Pointer to the shell structure.
 * @param flag Flag indicating specific behavior or properties of the addition.
 */
void					add_env_to_list(t_shell *shell, int flag);

/**
 * @brief Parses an environment variable string into key-value pairs.
 *
 * @param env_variable The environment variable string (key=value format).
 * @param flag Flag indicating specific behavior or properties of the parsing.
 * @param env_node Pointer to the environment variable node to populate.
 * @param index Pointer to the index used during parsing.
 * @return Integer indicating success or failure of the parsing.
 */
int						parse_key_value(char *env_variable, int flag,
							t_env **env_node, int *index);

/**
 * @brief Adds quotes around a given string.
 *
 * @param str The input string.
 * @return A newly allocated string with quotes added.
 */
char					*add_quote(char *str);

/**
 * @brief Removes quotes from a given string.
 *
 * @param str The input string with quotes.
 * @return A newly allocated string with quotes removed.
 */
char					*remove_quotes(char *str);

/**
 * @brief Assigns a value to an environment variable node.
 *
 * @param env_node Pointer to the environment variable node.
 * @param env_variable The environment variable string (key=value format).
 * @param start_index Pointer to the index used during assignment.
 * @return Integer indicating success or failure of the assignment.
 */
int						assign_value(t_env **env_node, char *env_variable,
							int *start_index);

/**
 * @brief Adds a new node to the end of the environment variables linked list.
 *
 * @param env_list Pointer to the head of the environment variables linked list.
 * @param new_node Pointer to the new node to add.
 */
void					env_lstadd_back(t_env **env_list, t_env *new_node);

/**

	* @brief This function ensures that the PWD and
	 OLDPWD environment variables are properly initialized
 * and updated in the shell's environment list. If PWD is not found,
	it is created with the
 * current working directory. If OLDPWD is not found,
	it is created with a NULL value.
 * @param shell Pointer to the shell structure.
 */
void					init_pwd_oldpwd(t_shell *shell);

/**
 * @brief Searches for a key in the shell's environment variables.
 *
 * @param shell Pointer to the shell structure.
 * @param key The key to search for in the environment.
 * @return Pointer to the value associated with the key, or NULL if not found.
 */
char					*search_in_env(t_shell *shell, char *key);

/**
 * @brief This function constructs a new environment variable string based on
 * the provided key, value, and export flag, and adds it to the shell's
 * environment list.
 * @param shell Pointer to the shell structure.
 * @param key The key of the environment variable.
 * @param value The value of the environment variable.
 * @param export_flag Flag indicating whether the variable should be exported.
 */
void					new_env(t_shell *shell, char *key, char *value,
							int export_flag);

/**
 * @brief Updates the shell level (SHLVL) environment variable.
 *
 * @param shell Pointer to the shell structure.
 */
void					update_shlvl(t_shell *shell);

/**
 * @brief Computes the new value for the shell level (SHLVL).
 *
 * @param value Current value of SHLVL.
 * @return Pointer to the new SHLVL value as a string.
 */
char					*shlvl_value(char *value);

/**
 * @brief Returns the updated shell level (SHLVL) value.
 *
 * @param value Current value of SHLVL.
 * @return Pointer to the updated SHLVL value as a string.
 */
char					*ft_return_shlvl(char *value);

/**
 * @brief Builds an abstract syntax tree (AST) from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root of the constructed AST.
 */
t_tree					*build_ast(t_token **tokens);

/**
 * @brief Builds an AST for logical AND operations from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root of the constructed AST for AND operations.
 */
t_tree					*build_ast_and(t_token **tokens);

/**
 * @brief Builds an AST for logical OR operations from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root of the constructed AST for OR operations.
 */
t_tree					*build_ast_or(t_token **tokens);

/**
 * @brief Builds an AST for pipe operations from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root of the constructed AST for pipe operations.
 */
t_tree					*build_ast_pipe(t_token **tokens);

/**
 * @brief Builds an AST for redirection operations from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.

	* @return Pointer to the root of the constructed 
	AST for redirection operations.
 */
t_tree					*build_ast_redirections(t_token **tokens);

/**
 * @brief Builds an AST for command execution from a list of tokens.
 *
 * @param tokens Pointer to the list of tokens.
 * @return Pointer to the root of the constructed AST for command execution.
 */
t_tree					*build_ast_command(t_token **tokens);

/**
 * @brief Handles the heredoc functionality in the shell.
 *
 * @param shell Pointer to the shell structure.
 * @param tokens Pointer to the list of tokens.
 */
void					heredoc(t_shell *shell, t_token *tokens);

/**
 * @brief Processes multiple heredocs in the token list.
 *
 * @param list Pointer to the token list.
 * @return int Returns a status code indicating success or failure.
 */
int						multiple_heredocs(t_token *list);

/**
 * @brief Checks if a character is a whitespace character.
 *
 * @param c Character to check.
 * @return int Returns non-zero if the character is a whitespace, otherwise 0.
 */
int						ft_isspace(int c);

/**
 * @brief Checks if a string consists entirely of whitespace characters.
 *
 * @param s Pointer to the string.
 * @return int Returns non-zero if the string is all whitespace, otherwise 0.
 */
int						is_all_space(const char *s);

/**
 * @brief Checks if a character is an operator.
 *
 * @param c Character to check.
 * @return int Returns non-zero if the character is an operator, otherwise 0.
 */
int						ft_isoperator(int c);

/**
 * @brief Skips spaces in a string and updates the index and sign.
 *
 * @param str Pointer to the string pointer.
 * @param i Pointer to the index variable.
 * @param sign Pointer to the sign variable.
 */
void					skip_spaces(char **str, int *i, int *sign);

/**
 * @brief Frees three pointers and sets them to NULL.
 *
 * @param a Pointer to the first variable to free.
 * @param b Pointer to the second variable to free.
 * @param c Pointer to the third variable to free.
 */
void					free_function(void **a, void **b, void **c);

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * @param array Pointer to the array of strings.
 */
void					ft_free_array(char **array);

/**
 * @brief Frees the environment list.
 *
 * @param env_list Pointer to the environment list.
 */
void					ft_free_envlist(t_env **env_list);

/**
 * @brief Clears the shell structure and optionally performs additional cleanup.
 *
 * @param shell Pointer to the shell structure.
 * @param flag Flag indicating the type of cleanup to perform.
 */
void					ft_clear(t_shell *shell, int flag);

/**
 * @brief Calculates the length of a string array.
 *
 * @param array Pointer to the array of strings.
 * @return int Returns the length of the array.
 */
int						ft_array_len(char **array);

/**
 * @brief Exits the shell and performs necessary cleanup.
 *
 * @param shell Pointer to the shell structure.
 */
void					exit_function(t_shell *shell);

/**
 * @brief Initializes signal handling for the shell.
 */
void					signal_init(void);

/**
 * @brief Handles a specific signal.
 * @param signal The signal to handle.
 */
void					handle_signal(int signal);

/**
 * @brief Configures signal handling for heredoc functionality.
 */
void					signal_heredoc(void);

/**
 * @brief Resets signal handling to default behavior.
 */
void					signal_dfl(void);

/**
 * @brief Handles signals specifically for heredoc operations.
 * @param signal The signal to handle.
 */
void					handle_heredoc(int signal);

/**
 * @brief Disables echo control characters in the terminal.
 */
void					disable_echoctl(void);

/**
 * @brief Enables echo control characters in the terminal.
 */
void					enable_echoctl(void);

/**
 * @brief Sets or retrieves the exit status of the shell.
 * @param str Optional string to parse for status.
 * @param status The status to set.
 * @return The current exit status.
 */
int						exit_status(char *str, int status);

/**
 * @brief Handles errors in the shell.
 * @param shell Pointer to the shell structure.
 * @param msg Error message to display.
 * @param error_type Type of error.
 * @param quote_flag Flag indicating if quotes are involved.
 */
void					handle_error(t_shell *shell, char *msg, int error_type,
							int quote_flag);

/**
 * @brief Prints an error message to the specified file descriptor.
 * @param args Arguments related to the error.
 * @param flag Flag indicating the type of error.
 * @param fd File descriptor to print the error to.
 */
void					ft_print_error(char *args, int flag, int fd);

/**
 * @brief Prints an error message based on the error code and token.
 * @param shell Pointer to the shell structure.
 * @param error_code Error code to interpret.
 * @param current Pointer to the current token.
 * @return Status code indicating success or failure.
 */
int						print_error(t_shell *shell, int error_code,
							t_token *current);

/**
 * @brief Executes the echo command.
 * @param args Arguments passed to the echo command.
 * @return Status code indicating success or failure.
 */
int						ft_echo(char **args);

/**
 * @brief Frees memory associated with a tree structure.
 * @param branch Pointer to the tree branch to free.
 */
void					ft_free_treelist(t_tree *branch);

/**
 * @brief Checks if a string consists only of numeric characters.
 *
 * @param str The string to check.
 * @return int Non-zero if the string is numeric, 0 otherwise.
 */
int						ft_isnumeric(const char *str);

/**

	* @brief Executes a command represented by the 
	AST node within the given shell context.
 *
 * @param shell Pointer to the shell context structure.
 * @param ast Pointer to the abstract syntax tree node representing the command.
 */
void					execute_command(t_shell *shell, t_tree *ast);

/**
 * @brief Changes the current working directory of the shell.
 *
 * @param args Array of arguments,
	where args[1] is typically the target directory.
 * @param shell Pointer to the shell context structure.
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int						ft_cd(char **args, t_shell *shell);

/**
 * @brief Updates or adds an environment variable in the shell.
 *
 * @param shell Pointer to the shell structure.
 * @param key The environment variable name.
 * @param value The value to set for the environment variable.
 */
void					update_env(t_shell *shell, char *key, char *value);

/**
 * @brief Prints the current working directory to standard output.
 *
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int						ft_pwd(void);

/**
 * @brief Prints the environment variables.
 *
 * @param env_list Pointer to the list of environment variables.
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int						ft_env(t_env *env_list);

/**
 * @brief Exits the shell with the specified arguments.
 *
 * @param args Array of arguments passed to the exit command.
 * @return int Returns the exit status.
 */
int						ft_exit(char **args, t_shell *shell);

/**
 * @brief Removes environment variables from the shell.
 *
 * @param args Array of environment variable names to unset.
 * @param shell Pointer to the shell structure.
 * @return int Returns 0 on success, or a non-zero value on failure.
 */
int						ft_unset(char **args, t_shell *shell);

int						is_valid_identifier(const char *str);

char					*ft_get_key(const char *arg);
char					*ft_get_value(const char *arg);
int						ft_export(char **args, t_shell *shell);
void					execute(t_shell *shell, t_tree *tree);
void					execute_pipe(t_shell *shell, t_tree *tree);
void					execute_redirections(t_shell *shell, t_tree *tree);
int						expand_redirection(t_shell *shell, t_tree *tree);
char					*expand_special_characters(char *input, int pos[2],
							char *result, t_shell *shell);
char					*handle_tilda(char *input, int pos[2], char *result,
							t_shell *shell);
char					*get_username(char *input, int pos[2]);
char					*ft_get_variable_value(char *input, int pos[2],
							t_shell *shell);
char					*handle_variable(char *input, int pos[2], char *result,
							t_shell *shell);
char					*get_quote_variable_value(char *input, int pos[2],
							t_shell *shell);
char					*handle_quotes_variable(char *input, int pos[2],
							char *result, t_shell *shell);
char					*handle_double_variable(char *input, int pos[2],
							char *result, t_shell *shell);
char					*expand_variables(char *input, int *pos,
							t_shell *shell);
char					*process_expansion(char *input, t_shell *shell);
char					*expand_exit_status(char *line, int index[2]);
char					*get_env_value(t_env *env_list, const char *var_name);
char					*get_var(char *line, int *index, t_env *env_list);
char					*get_variable_value(char *line, int pos[2],
							t_shell *shell);
char					*handle_variable_heredoc(char *line, int index[2],
							char *result, t_shell *shell);
char					*append_data(char *line, int index[2], char *result,
							int flag);
char					*expand_quotes_heredoc(char *str, int *cursor,
							t_shell *shell);
char					*expand_variables_heredoc(char *line, int *index,
							t_shell *shell);
char					*expansion_heredoc(char *line, t_shell *shell,
							char **temp);
void					expand_heredoc_to_file(t_shell *shell, int input_fd,
							int output_fd, t_tree *tree);
int						expand_command(t_shell *shell, t_tree *tree);
char					*clean_all_quotes(char *result);
void					ft_tolower_str(char **str);
int						ft_envlist_size(t_env *env_list);
char					*ft_strtrim_sides(char *str);
void					external_execution(t_shell *shell, t_tree *tree);
void					update_env_array(t_shell *shell, t_env *env_list,
							int total_vars);
void					signals_and_exitstatus(int status);
void					ft_dup(t_shell *shell);
void					close_fds(t_shell *shell);
void					ft_clear_subtree(t_subtree **subtree);
void					execute_subshell(t_shell *shell, t_tree *tree);
int						ft_str_cmd(char *s1, const char *s2);
int						handle_noexec(t_shell *shell, char *exec_path,
							char *cmd);
int						handle_exec_errors(t_shell *shell, char *exec_path,
							char *cmd, int found);

#endif