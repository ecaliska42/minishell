/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/18 19:25:57 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"


void	remove_quotes(t_token *token)
{
	int		i;
	char	*str;
	char		quote;

	i = 0;
	quote = CLOSED;
	str = token->str;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_check(str[i], &quote);
			//remove quote and skip to next char
			while (quote_check(str[i], &quote) != 0)
			{
				// skip while quote is open
			}
			// remove quote and check if word continues
		}
		i++;
	}
	token = token->next;
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}