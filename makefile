# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 15:50:49 by ecaliska          #+#    #+#              #
#    Updated: 2024/02/01 01:52:26 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc

FLAGS= -Wall -Werror -Wextra -lreadline -g

NAME= minishell

SRC= minishell.c

OBJ= $(SRC:.c=.o)

RM= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft all
	$(CC) $(FLAGS) -o $(NAME) $(SRC) libft/libft.a

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re:	fclean all
	$(MAKE) re -C libft

.PHONY: all clean fclean re