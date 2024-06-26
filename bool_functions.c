/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:55:01 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 16:40:07 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/parsing.h"

bool	ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool	ft_is_dollar(char c)
{
	if (c == '$')
		return (true);
	return (false);
}

bool	ft_is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
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
