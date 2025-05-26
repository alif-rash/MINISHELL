NAME = minishell
CC = cc 
CFLAG = -Wall -Werror -Wextra
RM = rm -f
SRCS = minishell.c tokenizer.c initialise.c utils.c env_utils.c shlvl.c \
		signals.c free.c ctrl_c.c error.c token_utils.c token_list_utils.c parsing.c \
		pwd_update.c
OBJS = ${SRCS:.c=.o}
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a
RLFLAGS		=	-lreadline -lhistory
RLDIR		=	-L/opt/vagrant/embedded/lib
RLINC		=	-I/opt/vagrant/embedded/include/readline/readline.h

%.o: %.c
	@${CC} ${CFLAG} ${RLINC} -c -o $@ $^

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAG} -o $@ $^ ${RLDIR} ${RLFLAGS} -L${LIBFT_DIR} -lft
	@echo "${GREEN}${NAME} created✅$(DEFAULT)"

${LIBFT}:
	@make -C ${LIBFT_DIR} bonus

all: ${NAME}

clean:
	@${RM} ${OBJS}
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