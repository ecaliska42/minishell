/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/07 19:13:24 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

int get_dquote_len(char *str, int i)
{
	int len;
	char *line;


	line = str;
	len = 0;

	i++;
	len++;
	while (line [i] != D_QUOTE && line[i] != '\0')
	{
		len++;
		i++;
	}
	i++;
	len++;
	printf("dquote_len: %d\n", len);
	return (len);
}

int get_squote_len(char *str, int i)
{
	int len;
	char *line;

	line = str;
	len = 0;
	i++;
	len++;
	while (line [i] != S_QUOTE && line[i] != '\0')
	{
		len++;
		i++;
	}
	i++;
	len++;
	printf("squote_len: %d\n", len);
	return (len);
}

int get_len(char *str, int i)
{
	char	*line;
	int		len;

	if (!str)
	{
		printf("Error: Null string passed.\n");
		return (-1);
	}
	len = 0;
	line = str;
	//while (line[i] != '\0')
	//{
		if (line[i] == S_QUOTE)
			get_squote_len(line, i);
		else if (line[i] == D_QUOTE)
			get_dquote_len(line, i);
		while (line[i] && (!(ft_is_space(line[i]))) && (!(ft_is_special(line[i])) && (!(ft_is_quote(line[i])))))
		{
				len++;
				i++;
		}
	//}
	printf("len: %d\n", len);
	return (len);
}

char *get_word(char *line, int *i)
{
	char	*word;
	int len;
	int index;
	int tmp;


	tmp = *i;
	index = 0;
	len = get_len(line, tmp);
	word = malloc(len + 1);
	if (!word)
	{
		printf("Get word error: malloc failed\n");
		exit(-1);
	}
	while (index < len)
	{
		word[index] = line[*i];
		printf("character at i=%d is: %c\n", *i, line[*i]);
		(*i)++;
		index++;
	}
	word[index] = '\0';
	return (word);
}


char *get_s_word(char *line, int *i)
{
	char	*word;
	int len;
	int index;
	int tmp;


	tmp = *i;
	index = 0;
	len = get_squote_len(line, tmp);
	word = malloc(len + 1);
	if (!word)
	{
		printf("Get word error: malloc failed\n");
		exit(-1);
	}
	while (index < len)
	{
		word[index] = line[*i];
		printf("character at i=%d is: %c\n", *i, line[*i]);
		(*i)++;
		index++;
	}
	word[index] = '\0';
	return (word);
}


char *get_d_word(char *line, int *i)
{
	char	*word;
	int len;
	int index;
	int tmp;


	tmp = *i;
	index = 0;
	len = get_dquote_len(line, tmp);
	word = malloc(len + 1);
	if (!word)
	{
		printf("Get word error: malloc failed\n");
		exit(-1);
	}
	while (index < len)
	{
		word[index] = line[*i];
		printf("character at i=%d is: %c\n", *i, line[*i]);
		(*i)++;
		index++;
	}
	word[index] = '\0';
	return (word);
}

void skip_spaces(char *line, int *i)
{
	while (line[*i] != '\0' && ft_is_space(line[*i]) == true)
		(*i)++;
}

t_token *add_new_empty_token(t_shell *shell)
{
	t_token *last_token;

	token_add(&shell->tokens);
	last_token = get_last_token(&shell->tokens);
	last_token->str = ft_strdup("");
	return (last_token);
}

void not_random(t_token *last_token, int *i)
{
	if (last_token->type == APPEND || last_token->type == HEREDOC)
		(*i)++;
	(*i)++;
}

void not_pipe(t_shell *shell, t_token *last_token, int *i)
{
	last_token->str = ft_strjoin(last_token->str, get_word(shell->input, i));
}

void handle_quote(t_shell *shell, t_token *last_token, char *line, int *i)
{
	if (squote_check(line[*i], &shell->quotes) == 1)
	{
		last_token->str = get_s_word(line, i);
		last_token->type = RANDOM;
		shell->quotes = CLOSED;
	}
	else if (dquote_check(line[*i], &shell->quotes) == 2)
	{
		last_token->str = get_d_word(line, i);
		last_token->type = RANDOM;
		shell->quotes = CLOSED;
	}
}

// void ft_str2tok(t_shell *shell, int *i)
// {
// 	char	*line;
// 	t_token	*last_token;

// 	if (!shell)
// 		return ;
// 	line = shell->input;
// 	skip_spaces(line, i);
// 	while (line[*i] != '\0')
// 	{
// 		last_token = add_new_empty_token(shell);
// 		if (ft_is_space(line[*i]) == true || ft_is_special(line[*i]) == true)
// 		{
// 			skip_spaces(line, i);
// 		}
// 		if (ft_is_quote(line[*i]))
// 			handle_quote(shell, last_token, line, i);
// 		ft_tokenizer(shell, last_token, *i);
// 		if (last_token->type != RANDOM)
// 			not_random(last_token, i);
// 		if (last_token->type != PIPE)
// 			not_pipe(shell, last_token, i);
// 	}
// }

void ft_str2tok(t_shell *shell, int *i)
{
	char	*line;
	t_token	*last_token;

	if (!shell)
		return ;
	line = shell->input;
	skip_spaces(line, i);
	while (line[*i] != '\0')
	{
		if (ft_is_quote(line[*i]))
		{
			last_token = add_new_empty_token(shell);
			handle_quote(shell, last_token, line, i);
			ft_tokenizer(shell, last_token, *i);
		}
		else if (ft_is_space(line[*i]) || ft_is_special(line[*i]))
		{
			skip_spaces(line, i);
			if (line[*i] != '\0')
			{
				last_token = add_new_empty_token(shell);
				ft_tokenizer(shell, last_token, *i);
			}
		}
		else
		{
			last_token = add_new_empty_token(shell);
			last_token->str = get_word(line, i);
			ft_tokenizer(shell, last_token, *i);
		}
		if (last_token->type != RANDOM)
			not_random(last_token, i);
		if (last_token->type != PIPE)
			not_pipe(shell, last_token, i);
		skip_spaces(line, i);
	}
}
