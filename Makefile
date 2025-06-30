NAME = minishell
CC = cc
CFLAG = -Wall -Werror -Wextra
RM = rm -f
SRCS = minishell.c \
	parsing/heredoc_multiple.c \
	parsing/heredoc.c \
	parsing/signals2.c \
	parsing/tree_utils.c \
	parsing/categorise_tokens.c \
	parsing/check_syntax.c \
	parsing/ctrl_c.c\
	parsing/env_utils.c\
	parsing/env_update.c\
	parsing/error.c\
	parsing/free.c\
	parsing/initialise.c\
	parsing/parsing.c \
	parsing/pwd_update.c \
	parsing/shlvl.c\
	parsing/shlvlutils.c\
	parsing/token_utils.c \
	parsing/signals.c\
	parsing/token_list_utils.c \
	parsing/token_utils.c \
	parsing/tokenizer.c \
	parsing/tree_commands.c \
	parsing/tree_create.c \
	parsing/tree_redirections.c \
	parsing/utils.c \
	parsing/utils1.c \
	execution/execute_command.c\
	execution/ft_cd.c \
	execution/ft_echo.c \
	execution/ft_env.c \
	execution/ft_exit.c \
	execution/ft_export.c \
	execution/ft_pwd.c \
	execution/ft_unset.c \
	execution/execution.c \
	execution/execute_pipe.c \
	execution/execute_redirections.c \
	execution/expansion.c \
	execution/expand_heredoc_variables.c \
	execution/expand_heredoc.c \
	execution/expand_redirections.c \
	execution/expansion_special_characters.c \
	execution/expansion_utils.c \
	execution/expand_command.c \
	execution/execute_external.c \
	execution/update_env_array.c \
	execution/execute_subshell.c \
	execution/utils.c \
	execution/export_utils.c
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, ${SRCS:.c=.o})
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAG} ${RLINC} -c -o $@ $^ -I .

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAG} -o $@ $^ ${RLDIR} ${RLFLAGS} -L${LIBFT_DIR} -lft
	@clear
	@for i in 1 2 3 4 5 6 7 8 9 10; do \
		printf "\n"; \
	done
	@printf "$(B_BLUE)"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗"
	@sleep 0.1
	@printf "%*s\n" $$(($$(tput cols)/2+35)) "╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝"
	@printf "$(DEFAULT)"
	@printf "\n\n"

${LIBFT}:
	@printf "$(CYAN)Building libft...$(DEFAULT)\r"
	@$(MAKE) -C ${LIBFT_DIR} bonus --no-print-directory
	@printf "                      \r"

all: ${NAME}

clean:
	@$(MAKE) -C ${LIBFT_DIR} clean --no-print-directory
	@${RM} -r ${OBJDIR}
	@echo "$(YELLOW)Object files cleaned 🧹$(DEFAULT)"

fclean: clean
	@$(MAKE) -C ${LIBFT_DIR} fclean --no-print-directory
	@${RM} ${NAME}
	@echo "$(RED)All files wiped away 🧼$(DEFAULT)"

re: fclean all

.PHONY: re fclean clean all

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
B_BLUE =\033[1;36m
DEFAULT = \033[0m