/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:58:46 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/17 14:41:44 by ecaliska         ###   ########.fr       */
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
