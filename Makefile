# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/04/09 15:36:20 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -lreadline -g
#FLAGS+= -fsanitize=address,undefined,leak

NAME= minishell

SRC= minishell.c buildins/ft_echo.c buildins/ft_cd.c buildins/ft_env.c \
	buildins/ft_exit.c buildins/ft_export.c buildins/ft_pwd.c buildins/ft_unset.c \
	parser.c execution_part/execute.c ms_utils.c \
	debugging/printf_double_tripple.c \
	buildins/buildin_check.c dup_and_close_functions.c\
	heredoc.c sizes/arrays.c sizes/lists.c\
	environment.c execution_part/execution_utils.c\
	booleans/bool_functions2.c\
	GNL/get_next_line.c GNL/get_next_line_utils.c\

SRC2 = lexer.c needed_functions.c print_debug.c token.c readline.c quote_stuff.c \
	syntax_check.c bool_functions.c expand.c

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

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=texts/readline.supp ./$(NAME)

exec: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re