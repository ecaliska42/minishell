/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/04 17:22:57 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (line [i] != '\"')
	{
		len++;
		i++;
	}
	i++;
	len++;
	printf("len: %d\n", len);
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
	while (line [i] != '\'')
	{
		len++;
		i++;
	}
	i++;
	len++;
	printf("len: %d\n", len);
	return (len);
}

int get_len(t_shell *shell, char *str, int i)
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
	while (line[i] && ((!(ft_is_space(line[i]))) || (quote_check(line[i], &shell->quotes) == 1)) && ((!(ft_is_special(line[i]))) || quote_check(line[i], &shell->quotes) == 1))
	{
		len++;
		i++;
	}
	return (len);
}

char *get_word(t_shell *quotes, char *line, int *i)
{
	char	*word;
	int len;
	int index;
	int tmp;


	tmp = *i;
	index = 0;
	len = get_len(quotes, line, tmp);
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


void ft_strtok(t_shell *shell, int *i)
{
	char	*line;
	size_t	k;
	t_token	*last_token;

	if (!shell)
		return ;
	k = 0;
	line = shell->input;
	shell->quotes = CLOSED;
	while (line[*i] != '\0')
	{
		token_add(&shell->tokens);
		last_token = get_last_token(&shell->tokens);
		if (squote_check(line[*i], &shell->quotes) == 1)
		{
			last_token->str = get_s_word(line, i);
			last_token->type = RANDOM;
			printf("line[i] is: %d\n", *i);
		}
		else if (dquote_check(line[*i], &shell->quotes) == 2)
		{
			last_token->str = get_d_word(line, i);
			last_token->type = RANDOM;
			printf("line[i] is: %d\n", *i);
		}
	}
}

void ft_str2tok(t_shell *shell, int *i)
{
	char	*line;
	size_t	k;
	t_token	*last_token;

	if (!shell)
		return ;
	k = 0;
	line = shell->input;

	while (line[*i] != '\0' && ft_is_space(line[*i]))
		(*i)++;
	while (line[*i] != '\0')
	{
		token_add(&shell->tokens);
		last_token = get_last_token(&shell->tokens);
		ft_tokenizer(shell, last_token, *i);
		printf("line[i] is: %d\n", *i);
		if (last_token->type != RANDOM)
		{
			if (last_token->type == APPEND || last_token->type == HEREDOC)
				(*i)++;
			(*i)++;
		}
		while (ft_is_space(line[*i]) == true)
			(*i)++;
		if (last_token->type != PIPE)
		{
			last_token->str = get_word(shell, line, i);
		}
	}
}
			// while (line[*i] != '\0' && ft_is_space(line[*i]))
			// 	(*i)++;
			// if (line[*i] != '\0')
			// {
			// 	// token_add(&shell->tokens);
			// 	// last_token = get_last_token(&shell->tokens);
			// 	ft_tokenizer(shell, last_token, *i);
			// 	printf("line[i] is: %d\n", *i);
			// 	if (last_token->type != RANDOM)
			// 	{
			// 		if (last_token->type == APPEND || last_token->type == HEREDOC)
			// 			(*i)++;
			// 		(*i)++;
			// 	}
			// 	while (ft_is_space(line[*i]) == true)
			// 		(*i)++;
			// 	if (last_token->type != PIPE)
			// 	{
			// 		last_token->str = get_word(shell, line, i);
			// 	}
		// }

// int	length_of_word(char *str, int i)
// {
// 	char	*line;
// 	int		len;

// 	if (!str)
// 	{
// 		printf("Error: Null string passed.\n");
// 		return (-1);
// 	}
// 	len = 0;
// 	line = str;
// 	while (line[i] != '\0')
// 	{
// 		len++;
// 		i++;
// 	}
// 	printf("len: %d\n", len);
// 	return (len);
// }
