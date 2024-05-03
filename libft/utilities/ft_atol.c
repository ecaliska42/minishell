/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:15 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/03 11:59:18 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <limits.h>
#include "../../libraries/minishell.h"

int	check_if_valid(long number, int digit, int sign)
{
	if (sign > 0 && (number > LONG_MAX / 10 || (number == LONG_MAX / 10
				&& digit > 7)))
		return (false);
	if (sign < 0 && (number < LONG_MAX / 10 || (number == LONG_MAX / 10
				&& digit > 8)))
		return (false);
	return (true);
}

long	ft_atol(const char *str)
{
	long	number;
	long	sign;
	int		i;

	number = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!check_if_valid(number, str[i] - '0', sign))
			return (return_write("Numeric arguments required", 2));
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
