/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:58:46 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/30 20:25:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

bool	is_only_numbers(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (true);
	while (s[i])
	{
		if (s[i] != '-' && s[i] != '+' && ft_isdigit(s[i]) == 0)
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
		if (ft_isdigit(s[i]) == 0 || ft_isalpha(s[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}
