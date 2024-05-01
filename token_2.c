/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:29:24 by mesenyur          #+#    #+#             */
/*   Updated: 2024/05/01 15:24:19 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
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

int	get_len(t_shell *shell, char *str, int *i)
{
	char	*line;
	int		len;

	if (!str)
		return (-1);
	len = 0;
	line = str;
	while (line[*i] != '\0' && ft_is_space(line[*i]) == false)
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

char	*get_word(t_shell *shell, char *line, int *i, t_mini *ms)
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
	tmp = *i;
	len = get_len(shell, line, i);
	word = ft_calloc(len + 2, sizeof(char));
	if (!word)
		check_malloc_exit(word, ms);
	while (index < len)
		word[index++] = line[tmp++];
	return (word);
}

int	not_pipe(t_shell *shell, t_token *last_token, int *i, t_mini *ms)
{
	last_token->str = get_word(shell, shell->input, i, ms);
	if (last_token->str == NULL)
	{
		ft_putendl_fd("minishell: syntax error", 2);
		return (ERROR);
	}
	return (SUCCESS);
}
