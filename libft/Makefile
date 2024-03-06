# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:00:21 by ecaliska          #+#    #+#              #
#    Updated: 2024/03/06 16:27:47 by mesenyur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=	cc

CFLAGS+=	-Wall -Werror -Wextra -g

SRC=	ft_fd/ft_putchar_fd.c ft_fd/ft_putendl_fd.c ft_fd/ft_putnbr_fd.c \
		ft_fd/ft_putstr_fd.c \
		utilitie/ft_atoi.c utilitie/ft_bzero.c utilitie/ft_calloc.c \
		utilitie/ft_itoa.c \
		to_is/ft_isalnum.c to_is/ft_isalpha.c to_is/ft_isascii.c to_is/ft_isdigit.c \
		to_is/ft_isprint.c to_is/ft_tolower.c to_is/ft_toupper.c to_is/ft_iswhitespace.c\
		lists/ft_lstadd_back.c lists/ft_lstadd_front.c lists/ft_lstclear.c \
		lists/ft_lstdelone.c lists/ft_lstiter.c lists/ft_lstlast.c lists/ft_lstmap.c \
		lists/ft_lstnew.c lists/ft_lstsize.c \
		mems/ft_memchr.c mems/ft_memcmp.c mems/ft_memcpy.c \
		mems/ft_memmove.c mems/ft_memset.c \
		strings/ft_split.c strings/ft_strchr.c strings/ft_strdup.c \
		strings/ft_striteri.c strings/ft_strjoin.c strings/ft_strlcat.c \
		strings/ft_strlcpy.c strings/ft_strlen.c strings/ft_strmapi.c strings/ft_strncmp.c \
		strings/ft_strnstr.c strings/ft_strrchr.c strings/ft_strtrim.c strings/ft_substr.c \

OBJ=	$(SRC:.c=.o)

NAME=	libft.a

RM=		rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:
	make fclean && make all

.PHONY: all clean fclean re
