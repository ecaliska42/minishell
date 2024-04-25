# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/04/25 15:15:22 by mesenyur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -g
LDFLAGS= -lreadline # linker directive
#FLAGS+= -fsanitize=address,undefined,leak

NAME= minishell

SRC= minishell.c \
	buildins/ft_echo.c buildins/ft_cd.c buildins/ft_cd2.c buildins/ft_env.c \
	buildins/ft_exit.c buildins/ft_cd3.c buildins/ft_export.c buildins/ft_export2.c buildins/ft_export3.c buildins/ft_export4.c buildins/ft_pwd.c buildins/ft_unset.c \
	buildins/buildin_check.c \
	parser/parser.c parser/parser2.c parser/parser3.c \
	execution_part/execute.c \
	ms_utils.c \
	dup_and_close_functions.c\
	sizes/arrays.c sizes/lists.c\
	heredoc.c environment.c\
	execution_part/execution_utils.c execution_part/child.c\
	booleans/bool_functions2.c\
	close.c \
	GNL/get_next_line.c GNL/get_next_line_utils.c\

SRC2 = lexer.c needed_functions.c print_debug.c token.c readline.c quote_stuff.c \
	syntax_check.c bool_functions.c expansion/expand.c signal.c free.c token_2.c extras.c \
	expansion/expand_2.c expansion/expand_3.c expansion/expand_4.c expansion/expand_5.c \
	free_2.c

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

libft:
	$(MAKE) -C libft

clean:
	$(RM) $(OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	rm -rf $(OBJ_DIR)
	$(MAKE) fclean -C libft
	

re:	fclean all
	$(MAKE) re -C libft

leak: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --suppressions=texts/readline.supp ./$(NAME)

fd:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=texts/readline.supp ./$(NAME)

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re leak run libft