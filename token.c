/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/01 17:10:27 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

void ft_strtok(t_shell *shell, int *i)
{
	char	*line;
	char	*copy;
	size_t		k;
	t_token	*last_token;

	if (!shell)
		return ;

	k = 0;
	line = shell->input;
	copy = line;
	while (copy[*i] != '\0')
	{
		if (quote_check(copy[*i], &shell->quotes) == CLOSED)
		{
			if (ft_is_space(copy[*i]))
				(*i)++;
			else
			{
				token_add(&shell->tokens);
				last_token = get_last_token(&shell->tokens);
				ft_tokenizer(shell, last_token, *i);
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
					last_token->str = get_word(copy, i);
				}
			}
		}
		else if (quote_check(copy[*i], &shell->quotes) == S_QUOTE)
		{
			while (copy[*i] != '\'' && copy[*i] != '\0')
			{
				shell->tokens->str[k++] = copy[(*i)++];
			}
			if (copy[*i] == '\'')
				(*i)++;

		}
		else if (quote_check(copy[*i], &shell->quotes) == D_QUOTE)
		{
			while (copy[*i] != '\"' && copy[*i] != '\0')
			{
				shell->tokens->str[k++] = copy[(*i)++];
			}
			if (copy[*i] == '\"')
				(*i)++;
		}
	}
}

char *get_word(char *line, int *i)
{
	char	*word;
	int len;
	int index;
	int tmp;

	tmp = *i;
	index = 0;
	//printf("line: %s\n", line);
	len = length_of_word(line, tmp);
	// word = ft_substr(line, *i, ft_strlen(line));
	word = malloc(len + 1);
	if (!word)
		exit(-1);
	while (index < len)
	{
		word[index] = line[*i];
		printf("character at i=%d is: %c\n", *i, line[*i]);
		(*i)++;
		//len--;
		index++;
	}
	word[index] = '\0';
	//printf("word: %s\n", word);
	return (word);
}

int	length_of_word(char *str, int i)
{
	char	*line;
	int		len;
	char	quotes;

	len = 0;
	quotes = CLOSED;
	line = str;
	while (ft_is_space(line[i]) == true)
		i++;
	while (!(ft_is_space(line[i])) && (quote_check(line[i], &quotes) || !(ft_is_special(line[i]))) && line[i] != '\0')
	{
		len++;
		//printf("line[*i]: %c\n", line[i]);
		i++;
	}
	if (quotes != CLOSED)
	{
		printf("unclosed quote\n");
	}
	printf("len: %d\n", len);
	return (len);
}
