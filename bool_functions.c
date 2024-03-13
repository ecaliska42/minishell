/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:55:01 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/12 14:08:35 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"

bool ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool ft_is_dollar(char c)
{
	if (c == '$')
		return (true);
	return (false);
}

bool ft_is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool ft_is_redirection(t_tokentype type)
{
	if (type == APPEND || type == OUTPUT
		|| type == INPUT || type == HEREDOC)
		return (true);
	return (false);
}
