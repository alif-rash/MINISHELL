# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raalifa <raalifa@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/21 12:45:57 by hparveen          #+#    #+#              #
#    Updated: 2025/06/18 10:13:07 by raalifa          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strcpy.c ft_strcmp.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
		ft_strndup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
		ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c get_next_line.c \
		get_next_line_utils.c 
BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c
OBJS = ${SRCS:.c=.o}
OBJBS = ${BONUS:.c=.o}
INCS = libft.h
NAME = libft.a
LIBC = ar rc
LIBR = ranlib
CC = cc
RM = rm -f
CFLAG = -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAG} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		@${LIBC} ${NAME} ${OBJS}
		@${LIBR} ${NAME}

all: ${NAME}

bonus: $(OBJBS) $(OBJS)
		@${LIBC} ${NAME}  ${OBJS} ${OBJBS}
		@${LIBR} ${NAME}

clean:
	 @${RM} ${OBJS} ${OBJBS}

fclean: clean
		@${RM} ${NAME}

re: fclean all

.PHONY: re fclean clean all bonus