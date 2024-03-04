/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:56:42 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/04 16:27:24 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int quotes_are_valid(t_shell *shell)
// {
// 	bool	s_closed;
// 	bool 	d_closed;
// 	int i;

// 	if (shell == NULL)
// 	{
// 		write(2, "shell is NULL\n", 14);
// 		exit (-1);
// 	}
// 	i = 0;
// 	s_closed = true;
// 	d_closed = true;
// 	while (shell->command_line[i] != '\0')
// 	{
// 		s_quotes_closed(shell->command_line[i], &s_closed);
// 		write(1, "here\n", 5);
// 		d_quotes_closed(shell->command_line[i], &d_closed);
// 		i++;
// 	}
// 	if (s_closed == false && d_closed == false)
// 	{
// 		write(2, "quote error\n", 12);
// 		exit (-1);
// 	}
// 	return (0);
// }

void d_quotes_closed(char index, char *quotes)
{
	if (index == '\"')
	{
		if (*quotes == CLOSED)
			*quotes = D_QUOTE;
		else if (*quotes == D_QUOTE)
			*quotes = CLOSED;
	}
}

void s_quotes_closed(char index, char *quotes)
{
	if (index == '\'')
	{
		if (*quotes == CLOSED)
			*quotes = S_QUOTE;
		else if (*quotes == S_QUOTE)
			*quotes = CLOSED;
	}
}

int squote_check(char index, char *quotes)
{
	s_quotes_closed(index, quotes);
	if (*quotes == S_QUOTE)
		return (1);
	return (0);
}


int dquote_check(char index, char *quotes)
{
	d_quotes_closed(index, quotes);
	if (*quotes == D_QUOTE)
		return (2);
	return (0);
}

int quote_check(char index, char *quotes)
{
	s_quotes_closed(index, quotes);
	d_quotes_closed(index, quotes);
	if (*quotes == D_QUOTE || *quotes == S_QUOTE)
		return (3);
	return (0);
}