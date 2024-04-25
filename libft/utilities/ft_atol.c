/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:15 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/25 15:21:51 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <limits.h>

int	check_if_valid(long number, int digit, int sign)
{
	if (sign > 0 && (number > LONG_MAX / 10 || (number == LONG_MAX / 10
				&& digit > 7)))
		return (false);
	if (sign < 0 && (number < LONG_MIN / 10 || (number == LONG_MIN / 10
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
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (!check_if_valid(number, str[i] - '0', sign))
		{
			ft_putendl_fd("Numeric argument required", 2);
			return (2);
		}
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
