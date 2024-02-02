# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 15:50:49 by ecaliska          #+#    #+#              #
#    Updated: 2024/02/02 17:50:32 by ecaliska         ###   ########.fr        #
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

gitpush: fclean
	@echo "pushing in github"
	@echo "."
	@git add * 2>/dev/null
	@echo ".."
	@git commit -m "Makefile pushing" 2>/dev/null
	@echo "..."
	@git push 2>/dev/null
	@echo "PUSHED TO YOUR GITHUB"

.PHONY: all clean fclean re gitpush