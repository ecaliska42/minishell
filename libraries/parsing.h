/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melsen6 <melsen6@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:44:12 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/28 00:05:10 by melsen6          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define CLOSED 0
# define D_QUOTE '\"'
# define S_QUOTE '\''
# define PROMPT "🨀 ShellMate 🨁 :~ "
# define SUCCESS 0
# define ERROR 1
// # define DELIM " \n\t\r\v\f"
# define SYNTAX_ERROR 2
# define MALLOC_ERROR 62

# define READLINE 1
# define CHILD 2
# define NON_INTERACTIVE 3
# define HERDOC 4

typedef enum e_tokentype
{
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	OUTPUT,
	RANDOM,
}					t_tokentype;

typedef struct s_expansion
{
	char	*tmp;
	char	*value;
	char	*tmp_i;
	char	*joker;
	char	quotes;
	int		len;
	int		i;
	int		word_count;
	int		join;
	int		split;
	int		replace;
}			t_expansion;

typedef struct s_token
{
	char			*str;
	// int				token_count;
	int				expanded;
	bool			ambiguous;
	bool			flag_exp;
	bool			empty;
	t_tokentype		type;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			*input;
	char			quotes;
	struct s_token	*tokens;
}					t_shell;

// main
void				ft_init_shell(t_shell *shell);

// tokenizing
t_token				*get_last_token(t_token **tokens);
int					token_add(t_token **tokenlist);
void				ft_tokenizer(t_shell *shell, t_token *last, int i);
int					ft_strtok(t_shell *shell, int *i);
char				*get_word(t_shell *shell, char *line, int *i);
int					token_add(t_token **token);
void				tokenize(t_shell *shell, int *i, bool is_quote);

// lexer
int					lexical_analyzer(t_shell *shell);
int					syntax_check(t_shell *shell);

// quotes
void				d_quotes_closed(char index, char *quotes);
void				s_quotes_closed(char index, char *quotes);
int					squote_check(char index, char *quotes);
int					dquote_check(char index, char *quotes);
int					quote_check(char index, char *quotes);
void				handle_quote(t_shell *shell, t_token *last_token,
						char *line, int *i);
// bool
bool				ft_is_quote(char c);
bool				ft_is_space(char c);
bool				ft_is_special(char c);
bool				ft_is_dollar(char c);
bool				ft_is_redirection(t_tokentype shell);

// print - remove before push
void				print_everything(t_shell *shell);

bool				break_character(t_shell *shell, char *line, int i);
void				skip_spaces(char *line, int *i);
int					check_name_and_return_len(char *name);
int					ft_strcmp(const char *s1, const char *s2);
void				insert_token(char **str, t_token *token, t_token *n_token);

int					syntax_before_token(t_shell *shell);
void				free_and_null(void **ptr);

// TOKENIZING
int					not_pipe(t_shell *shell, t_token *last_token, int *i);
t_token				*add_new_empty_token(t_shell *shell);

#endif