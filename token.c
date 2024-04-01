/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/28 18:03:37 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/parsing.h"

int	get_dquote_len(t_shell *shell, char *str, int **i)
{
	int		len;
	char	*line;

	line = str;
	len = 0;
	(**i)++;
	len++;
	while (line[**i] != D_QUOTE && line[**i] != '\0')
	{
		len++;
		(**i)++;
	}
	quote_check(line[**i], &shell->quotes);
	(**i)++;
	len++;
	return (len);
}

int	get_squote_len(t_shell *shell, char *str, int **i)
{
	int		len;
	char	*line;

	line = str;
	len = 0;
	(**i)++;
	len++;
	while (line[**i] != S_QUOTE && line[**i] != '\0')
	{
		len++;
		(**i)++;
	}
	quote_check(line[**i], &shell->quotes);
	(**i)++;
	len++;
	return (len);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] != '\0' && ft_is_space(line[*i]) == true)
		(*i)++;
}

int	get_len(t_shell *shell, char *str, int *i)
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
	while (line[*i] != '\0')
	{
		if (break_character(shell, line, *i) == true)
			break ;
		if (line[*i] == S_QUOTE)
			len += get_squote_len(shell, line, &i);
		if (line[*i] == D_QUOTE)
			len += get_dquote_len(shell, line, &i);
		while (line[*i] != '\0' && ft_is_space(line[*i]) == false
			&& ft_is_special(line[*i]) == false
			&& ft_is_quote(line[*i]) == false)
		{
			len++;
			(*i)++;
		}
	}
	return (len);
}

bool	break_character(t_shell *shell, char *line, int i)
{
	if (quote_check(line[i], &shell->quotes) == 0)
	{
		if (ft_is_space(line[i]) == true || ft_is_special(line[i]) == true)
			return (true);
	}
	return (false);
}

char	*get_word(t_shell *shell, char *line, int *i)
{
	char	*word;
	int		len;
	int		index;
	int		tmp;

	index = 0;
	while (ft_is_space(line[*i]) == true && line[*i] != '\0')
		(*i)++;
	if (ft_is_special(line[*i]) == true)
		printf("PROBLEM!!!special character at i=%d is: %c\n", *i, line[*i]);
	tmp = *i;
	len = get_len(shell, line, i);
	word = malloc(len + 1);
	if (!word)
	{
		printf("Get word error: malloc failed\n");
		exit(-1);
	}
	while (index < len)
	{
		word[index] = line[tmp];
		tmp++;
		index++;
	}
	word[index] = '\0';
	return (word);
}

t_token	*add_new_empty_token(t_shell *shell)
{
	t_token	*last_token;

	token_add(&shell->tokens);
	last_token = get_last_token(&shell->tokens);
	return (last_token);
}

void	not_random(t_token *last_token, int *i)
{
	if (last_token->type == APPEND || last_token->type == HEREDOC)
		(*i)++;
	(*i)++;
}

void	not_pipe(t_shell *shell, t_token *last_token, int *i)
{
	last_token->str = get_word(shell, shell->input, i);
}

void	ft_strtok(t_shell *shell, int *i)
{
	char	*line;
	t_token	*last_token;

	if (!shell)
		return ;
	line = shell->input;
	while (line[*i] != '\0')
	{
		if (ft_is_space(line[*i]) == true && line[*i] != '\0')
		{
			(*i)++;
			continue ;
		}
		last_token = add_new_empty_token(shell);
		ft_tokenizer(shell, last_token, *i);
		if (last_token->type != RANDOM)
			not_random(last_token, i);
		if (last_token->type == PIPE)
		{
			while (ft_is_space(line[*i]) == true && line[*i] != '\0')
				(*i)++;
			if (line[*i] != '\0')
			{
				last_token = add_new_empty_token(shell);
				ft_tokenizer(shell, last_token, *i);
				if (last_token->type != RANDOM)
					not_random(last_token, i);
			}
		}
		not_pipe(shell, last_token, i);
	}
}

// char *get_s_word(char *line, int *i)
// {
// 	char	*word;
// 	int len;
// 	int index;
// 	int tmp;

// 	tmp = *i;
// 	index = 0;
// 	len = get_squote_len(line, tmp);
// 	word = malloc(len + 1);
// 	if (!word)
// 	{
// 		printf("Get word error: malloc failed\n");
// 		exit(-1);
// 	}
// 	while (index < len)
// 	{
// 		word[index] = line[*i];
// 		printf("character at i=%d is: %c\n", *i, line[*i]);
// 		(*i)++;
// 		index++;
// 	}
// 	word[index] = '\0';
// 	return (word);
// }

// char *get_d_word(char *line, int *i)
// {
// 	char	*word;
// 	int len;
// 	int index;
// 	int tmp;

// 	tmp = *i;
// 	index = 0;
// 	len = get_dquote_len(line, tmp);
// 	word = malloc(len + 1);
// 	if (!word)
// 	{
// 		printf("Get word error: malloc failed\n");
// 		exit(-1);
// 	}
// 	while (index < len)
// 	{
// 		word[index] = line[*i];
// 		printf("character at i=%d is: %c\n", *i, line[*i]);
// 		(*i)++;
// 		index++;
// 	}
// 	word[index] = '\0';
// 	return (word);
// }

// void handle_quote(t_shell *shell, t_token *last_token, char *line, int *i)
// {
// 	if (squote_check(line[*i], &shell->quotes) == 1)
// 	{
// 		last_token->str = get_word(shell, line, i);
// 		last_token->type = RANDOM;
// 		shell->quotes = CLOSED;
// 	}
// 	else if (dquote_check(line[*i], &shell->quotes) == 2)
// 	{
// 		last_token->str = get_word(shell, line, i);
// 		last_token->type = RANDOM;
// 		shell->quotes = CLOSED;
// 	}
// }