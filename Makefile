# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/04/22 12:18:43 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -g
LDFLAGS= -lreadline # linker directive
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
	execution_part/child.c\
	GNL/get_next_line.c GNL/get_next_line_utils.c\

SRC2 = lexer.c needed_functions.c print_debug.c token.c readline.c quote_stuff.c \
	syntax_check.c bool_functions.c expansion/expand.c signal.c free.c token_2.c extras.c \
	expansion/expand_2.c expansion/expand_3.c expansion/expand_4.c

#OBJ= $(SRC:.c=.o) $(SRC2:.c=.o)

#TEMPORARY CREATES A DIRECTORY FOR OBJECT FILES
OBJ_DIR= obj
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o) $(SRC2:.c=.o))

RM= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft all
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(SRC2) libft/libft.a $(LDFLAGS)

#TEMPORARY CREATES A DIRECTORY FOR OBJECT FILES
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) fclean -C libft
	

re:	fclean all
	$(MAKE) re -C libft

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=texts/readline.supp ./$(NAME)

exec: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re