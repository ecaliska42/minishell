# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 18:00:21 by ecaliska          #+#    #+#              #
#    Updated: 2024/04/29 14:54:33 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=	cc

CFLAGS=	-Wall -Werror -Wextra -g

SRC=	ft_fd/ft_putchar_fd.c ft_fd/ft_putendl_fd.c ft_fd/ft_putnbr_fd.c \
		ft_fd/ft_putstr_fd.c \
		utilities/ft_atoi.c utilities/ft_bzero.c utilities/ft_calloc.c \
		utilities/ft_itoa.c utilities/ft_atol.c \
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

#OBJ=	$(SRC:.c=.o)

OBJ_DIR= obj
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

NAME=	libft.a

RM=		rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

#%.o: %.c
#	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) $(OBJ)
	rm -rf $(OBJ_DIR)

fclean:	clean
	rm -rf $(OBJ_DIR)
	$(RM) $(NAME)

re:
	make fclean && make all

.PHONY: all clean fclean re
