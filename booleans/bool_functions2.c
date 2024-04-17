/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:58:46 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/17 16:04:41 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

bool	is_only_numbers(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (true);
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

bool	is_alpha_numbers(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (true);
	while (s[i])
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	first_character_is(char *s, char c)
{
	if (!s)
		return (false);
	while (ft_is_white_space(*s) == true)
	{
		s++;
	}
	if (*s == c)
		return (true);
	return (false);
}
