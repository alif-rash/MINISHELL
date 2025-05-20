NAME = minishell
CC = cc 
CFLAG = -Wall -Werror -Wextra
RM = rm -f
SRCS = minishell.c initial_check.c tokenizer.c initialise.c utils.c env_utils.c env_handle.c shlvl.c
OBJS = ${SRCS:.c=.o}
LIBFT_DIR = libft
LIBFT = ${LIBFT_DIR}/libft.a

%.o: %.c
	@${CC} ${CFLAG} -c -o $@ $^

${NAME}: ${OBJS} ${LIBFT}
	@${CC} ${CFLAG} -o $@ $^ -L${LIBFT_DIR} -lft -lreadline
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