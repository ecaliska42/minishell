/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:44:12 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/16 14:56:03 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

// # define EMPTY 0 // ""
// # define PIPE 1 // |
// # define APPEND 2 // >>
// # define OUTPUT 3 // >s
// # define INPUT 4 // <
// # define HEREDOC 5 // <<

# define CLOSED 0
# define D_QUOTE '\"'
# define S_QUOTE '\''
//# define PROMPT "Minishell:~$ "
# define PROMPT "🨀 ShellMate 🨁 :~ "
# define SUCCESS 0
# define ERROR 1
# define DELIM " \n\t\r\v\f"
# define SYNTAX_ERROR 2
# define MALLOC_ERROR 62
# define left '<'
# define right '>'
//SIGNALS
# define READLINE 1
# define CHILD 2
# define NON_INTERACTIVE 3
# define HERDOC 4

typedef enum e_tokentype
{
	PIPE,   // | 7
	HEREDOC, // <<
	APPEND,  // >>
	INPUT,   // <
	OUTPUT,   // >
	RANDOM,
}			t_tokentype;

typedef struct s_token
{
	char	*str;
	bool 	ambiguous;
	bool 	flag_exp;
	t_tokentype	type;
	struct s_token	*next;
}			t_token;

typedef struct s_shell
{
	char	*input;
	char 	quotes;
	struct s_token *tokens;
}			t_shell;

//main
void 	ft_init_shell(t_shell *shell);

//tokenizing
t_token *get_last_token(t_token **tokens);
int 	token_add(t_token **tokenlist);
void 	ft_tokenizer(t_shell *shell, t_token *last, int i);
int	ft_strtok(t_shell *shell, int *i);
char 	*get_word(t_shell *shell, char *line, int *i);
int 	token_add(t_token **token);
void 	free_tokens(t_token **tokens);
void 	tokenize(t_shell *shell, int *i, bool is_quote);

//lexer
int 	lexical_analyzer(t_shell *shell);
int		syntax_check(t_shell *shell);

//quotes
void	d_quotes_closed(char index, char *quotes);
void	s_quotes_closed(char index, char *quotes);
int		squote_check(char index, char *quotes);
int		dquote_check(char index, char *quotes);
int		quote_check(char index, char *quotes);
void	handle_quote(t_shell *shell, t_token *last_token, char *line, int *i);
//bool
bool	ft_is_quote(char c);
bool	ft_is_space(char c);
bool	ft_is_special(char c);
bool	ft_is_dollar(char c);
bool	ft_is_redirection(t_tokentype shell);

//print - remove before push
void 	print_everything(t_shell *shell);

bool 	break_character(t_shell *shell, char *line, int i);
void	skip_spaces(char *line, int *i);
int		check_name_and_return_len(char *name);
int		ft_strcmp(const char *s1, const char *s2);
t_token	*split_value(char *str, char *value, t_token *token);//, int flag);
// void	split_value(char *str, t_token *token);
void 	insert_token(char **str, t_token *token, t_token *n_token);



#endif