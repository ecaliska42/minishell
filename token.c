/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/08 17:54:15 by ecaliska         ###   ########.fr       */
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
		// while (line[*i] != '\0' && ft_is_space(line[*i]) == false
		// 	&& ft_is_special(line[*i]) == false
		// 	&& ft_is_quote(line[*i]) == false)
		// {
		// 	len++;
		// 	(*i)++;
		// }
		else if (line[*i] != '\0' && ft_is_space(line[*i]) == false
			&& ft_is_special(line[*i]) == false
			&& ft_is_quote(line[*i]) == false)
		{
			len++;
			(*i)++;
		}
		else
			break;
		// printf("line[*i] = '%c'\n", line[*i]);
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
		return (NULL);
		// printf("PROBLEM!!!special character at i=%d is: %c\n", *i, line[*i]);
	tmp = *i;
	len = get_len(shell, line, i);
	word = ft_calloc(len + 2, sizeof(char));
	if (!word)
	{
		printf("Get word error: malloc failed\n");
		return (NULL);
		// exit(-1);
	}
	while (index < len)
	{
		word[index++] = line[tmp++];
	}
	// word[index] = '\0';
	return (word);
}

t_token	*add_new_empty_token(t_shell *shell)
{
	t_token	*last_token;

	if (token_add(&shell->tokens) == -1)
	{
		printf("Error: Token add failed\n");
		return (NULL);
	}
	last_token = get_last_token(&shell->tokens);
	return (last_token);
}

void	not_random(t_token *last_token, int *i)
{
	if (last_token->type == APPEND || last_token->type == HEREDOC)
		(*i)++;
	(*i)++;
}

int	not_pipe(t_shell *shell, t_token *last_token, int *i)
{
	last_token->str = get_word(shell, shell->input, i);
	if (last_token->str == NULL)
	{
		ft_putendl_fd("Error: get_word failes", 2);
		// printf("Error: get_word failed\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_strtok(t_shell *shell, int *i)
{
	char	*line;
	t_token	*last_token;

	if (!shell)
		return (ERROR);
	line = shell->input;
	while (line[*i] != '\0')
	{
		if (ft_is_space(line[*i]) == true && line[*i] != '\0')
		{
			(*i)++;
			continue ;
		}
		last_token = add_new_empty_token(shell);
		if (!last_token)
		{
			printf("Error: Token add failed\n");
			return (ERROR);
		}
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
		if (not_pipe(shell, last_token, i) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
