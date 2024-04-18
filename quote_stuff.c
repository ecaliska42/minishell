/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:56:42 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 16:16:59 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"

void	change_dquote(char index, char *quotes)
{
	if (index == '\"')
	{
		if (*quotes == CLOSED)
			*quotes = D_QUOTE;
		else if (*quotes == D_QUOTE)
			*quotes = CLOSED;
	}
}

void	change_squote(char index, char *quotes)
{
	if (index == '\'')
	{
		if (*quotes == CLOSED)
			*quotes = S_QUOTE;
		else if (*quotes == S_QUOTE)
			*quotes = CLOSED;
	}
}

int	squote_check(char index, char *quotes)
{
	change_squote(index, quotes);
	if (*quotes == S_QUOTE)
		return (1);
	return (0);
}

int	dquote_check(char index, char *quotes)
{
	change_dquote(index, quotes);
	if (*quotes == D_QUOTE)
		return (2);
	return (0);
}

int	quote_check(char index, char *quotes)
{
	squote_check(index, quotes);
	dquote_check(index, quotes);
	if (*quotes == D_QUOTE || *quotes == S_QUOTE)
	{
		if (*quotes == D_QUOTE)
			return (2);
		else
			return (1);
	}
	return (0);
}
