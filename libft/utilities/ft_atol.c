/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:27:15 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/24 17:27:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <limits.h>

long	ft_atol(const char *str)
{
	long	number;
	int		sign;
	int		i;

	number = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > LONG_MAX / 10
			|| (number == LONG_MAX / 10 && str[i] - '0' > 7))
			return (-2147483649);
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}
