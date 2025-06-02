NAME = minishell
CC = cc 
CFLAG = -Wall -Werror -Wextra
RM = rm -f
SRCS = minishell.c \
	execution.c \
	parsing/heredoc_multiple.c \
	parsing/heredoc.c \
	parsing/signals2.c \
	parsing/tree_utils.c \
	parsing/categorise_tokens.c \
	parsing/check_syntax.c \
	parsing/ctrl_c.c\
	parsing/env_utils.c\
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
	execution/ft_pwd.c \
	execution/ft_echo.c \

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/, ${SRCS:.c=.o})
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@${CC} ${CFLAG} ${RLINC} -c -o $@ $^ -I .

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAG} -o $@ $^ ${RLDIR} ${RLFLAGS} -L${LIBFT_DIR} -lft
	@echo "${GREEN}${NAME} created✅$(DEFAULT)"

${LIBFT}:
	@make -C ${LIBFT_DIR} bonus

all: ${NAME}

clean:
	@${RM} -r ${OBJDIR}
	@make clean -C ${LIBFT_DIR}
	@echo "$(YELLOW)Object files cleaned 🧹$(DEFAULT)"

fclean: clean
	@${RM} ${NAME}
	@make fclean -C ${LIBFT_DIR}
	@echo "$(RED)All files wiped away 🧼$(DEFAULT)"

re: fclean all

.PHONY: re fclean clean all

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m