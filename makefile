# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 15:50:49 by ecaliska          #+#    #+#              #
#    Updated: 2024/03/15 18:14:07 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -lreadline -g

NAME= minishell

SRC= minishell.c buildins/ft_echo.c buildins/ft_cd.c buildins/ft_env.c \
	buildins/ft_exit.c buildins/ft_export.c buildins/ft_pwd.c buildins/ft_unset.c \
	parser_temp.c execution_part/execute.c ms_utils.c \
	debugging/printf_double_tripple.c \
	buildin_check.c dup_and_close_functions.c\
	heredoc.c sizes/arrays.c sizes/lists.c\

SRC2 = lexer.c needed_functions.c print_debug.c token.c readline.c quote_stuff.c \
	syntax_check.c bool_functions.c

OBJ= $(SRC:.c=.o) $(SRC2:.c=.o)

RM= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft all
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(SRC2) libft/libft.a

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re:	fclean all
	$(MAKE) re -C libft

.PHONY: all clean fclean re