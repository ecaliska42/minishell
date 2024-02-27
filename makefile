# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 15:50:49 by ecaliska          #+#    #+#              #
#    Updated: 2024/02/27 18:48:49 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -lreadline -g

NAME= minishell

SRC= minishell.c buildins/ft_echo.c buildins/ft_cd.c buildins/ft_env.c \
	buildins/ft_exit.c buildins/ft_export.c buildins/ft_pwd.c buildins/ft_unset.c \
	parser_temp.c execution_part/execute.c ms_utils.c \
	get_first_word_after_char.c printf_double_tripple.c get_first_word.c\
	

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