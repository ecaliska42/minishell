/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:44:12 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/28 18:59:41 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

// # define EMPTY 0 // ""
// # define PIPE 1 // |
// # define APPEND 2 // >>
// # define TRUNC 3 // >s
// # define INPUT 4 // <
// # define HEREDOC 5 // <<

# define CLOSED 0
# define D_QUOTE '\"'
# define S_QUOTE '\''
# define PROMPT "Minishell:~$ "
# define SUCCESS 0
# define ERROR 1
# define DELIM " \n\t\r\v\f"
# define SYNTAX_ERROR 2
# define MALLOC_ERROR 62

typedef enum e_tokentype
{
	PIPE,    // |
	APPEND,  // >>
	TRUNC,   // >
	INPUT,   // <
	HEREDOC, // <<
	RANDOM,
	// OUTFILE,
	// INFILE,
}			t_tokentype;

typedef struct s_token
{
	char	*str;
	t_tokentype	type;
	struct s_token	*next;
}			t_token;

// tokens_functions:
int 	token_add(t_token **tokenlist);

typedef struct s_shell
{
	char	*input;
	char 	quotes;
	struct s_token *tokens;
}			t_shell;

//main

void 	ft_init_shell(t_shell *shell);
int 	ft_readline(t_shell *shell);

//tokenizing
void 	ft_tokenizer(t_shell *shell, int *i);
void 	ft_strtok(t_shell *shell, int *i);
int		tokenizing_first_operator(char *str, t_shell *shell);
int 	length_of_word(t_shell *shell, int *i);
char 	*get_word(char *line, int *i);
void 	print_tokens(t_shell *shell);
int 	token_add(t_token **token);
// void 	ft_tokensfree(t_token *tokens);

//lexer
int 	lexical_analyzer(t_shell *shell);
int		syntax_check(t_shell *shell);

//quotes
void	d_quotes_closed(char index, char *quotes);
void	s_quotes_closed(char index, char *quotes);
int		quote_check(char index, char *quotes);

//bool
bool	ft_is_quote(char c);
bool	ft_is_space(char c);
bool	ft_is_special(char c);
bool	ft_is_dollar(char c);

// unsure
bool	ft_is_redirection(t_tokentype shell);
bool	ft_is_redin(t_shell *shell);
bool	ft_is_redout(t_shell *shell);
char	*get_infile(t_shell *shell);
char	*get_outfile(t_shell *shell);
int		ft_strcmp(const char *s1, const char *s2);
void 	print_everything(t_shell *shell);

#endif