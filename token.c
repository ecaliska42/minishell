/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/29 14:45:55 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>

void ft_strtok(t_shell *shell, int *i)
{
	char	*line;
	char	*copy;
	size_t		k;

	if (!shell)
		return ;

	k = 0;
	line = shell->input;
	copy = line;
	while (copy[*i] != '\0')
	{
		// if (k >= ft_strlen(shell->tokens->str))
		// 	break;
		if (quote_check(copy[*i], &shell->quotes) == CLOSED)
		{
			printf("quotes: %c\n", shell->quotes);
			if (ft_strchr(DELIM, copy[*i]))
				(*i)++;
			else
			{
				token_add(&shell->tokens);
				ft_tokenizer(shell, i);
				if (shell->tokens->type != PIPE)
				{
					shell->tokens->str = get_word(line, i);
				}
				(*i)++;
			}
		}
		else if (quote_check(copy[*i], &shell->quotes) == S_QUOTE)
		{
			printf("quotes: %c\n", shell->quotes);
			while (copy[*i] != '\'' && copy[*i] != '\0')
			{
				shell->tokens->str[k++] = copy[(*i)++];
			}
			if (copy[*i] == '\'')
				(*i)++;

		}
		else if (quote_check(copy[*i], &shell->quotes) == D_QUOTE)
		{
			printf("quotes: %c\n", shell->quotes);
			while (copy[*i] != '\"' && copy[*i] != '\0')
			{
				shell->tokens->str[k++] = copy[(*i)++];
			}
			if (copy[*i] == '\"')
				(*i)++;
		}
	}
	shell->tokens->str[k] = '\0';
}

char *get_word(char *line, int *i)
{
	t_shell	shell;
	char	*word;
	int len;
	int index;

	index = 0;
	len = length_of_word(&shell, i);
	word = malloc(len + 1);
	if (!word)
		exit(-1);
	while (len > 0)
	{
		word[index++] = line[*i];
		(*i)++;
		len--;
	}
	word[index] = '\0';
	// word = ft_substr(line, *i, ft_strlen(line));
	return (word);
}

int	length_of_word(t_shell *shell, int *i)
{
	char	*line;
	int		len;
	char	quotes;

	printf("i is: %d\n", *i);
	len = 0;
	quotes = CLOSED;
	line = shell->input;
	printf("line[*i]: %c\n", line[*i]);
	while (ft_is_space(line[*i]) == true)
		(*i)++;
	while (!(ft_is_space(line[*i])) && (quote_check(line[*i], &quotes) || !(ft_is_special(line[*i]))) && line[*i] != '\0')
	{
		len++;
		printf("len: %d\n", len);
		printf("line[*i]: %c\n", line[*i]);
		(*i)++;
	}
	if (quotes != CLOSED)
	{
		printf("unclosed quote\n");
	}
	return (len);
}
