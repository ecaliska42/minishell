# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/04/30 19:11:57 by ecaliska         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC= cc
#REMOVE -G FLAG (MAY SLOW DOWN PROGRAMM)
FLAGS= -Wall -Werror -Wextra -g
LDFLAGS= -lreadline # linker directive

NAME= minishell

SRC= minishell.c \
	buildins/ft_echo.c buildins/ft_cd.c buildins/ft_cd2.c buildins/ft_env.c \
	buildins/ft_exit.c buildins/ft_cd3.c buildins/ft_export.c buildins/ft_export2.c buildins/ft_export3.c buildins/ft_export4.c buildins/ft_pwd.c buildins/ft_unset.c \
	buildins/buildin_check.c buildins/ft_export5.c buildins/ft_cd4.c\
	parser/parser.c parser/parser2.c parser/parser3.c parser/parser4.c\
	ms_utils.c \
	dup_and_close_functions.c dup2.c\
	sizes/arrays.c sizes/lists.c\
	heredoc.c environment.c\
	execution_part/execution_utils.c execution_part/child.c execution_part/execute.c execution_part/child2.c\
	booleans/bool_functions2.c\
	close.c \

SRC2 = lexer.c needed_functions.c token.c readline.c quote_stuff.c \
	syntax_check.c bool_functions.c expansion/expand_1.c signal.c free.c token_2.c extras.c \
	expansion/expand_2.c expansion/expand_3.c expansion/expand_4.c expansion/expand_5.c \
	free_2.c expansion/expand_6.c free3.c\

OBJ_DIR= obj
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o) $(SRC2:.c=.o))

RM= rm -f

all: $(NAME)

$(NAME): $(OBJ)
	make -C ./libft all
	$(CC) $(FLAGS) -o $(NAME) $(SRC) $(SRC2) libft/libft.a $(LDFLAGS)

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
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes --suppressions=$(HOME)/readline.supp ./$(NAME)

.PHONY: all clean fclean re libft