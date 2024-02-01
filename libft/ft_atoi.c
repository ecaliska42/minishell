/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:50 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:47:18 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number(const char *nptr)
{
	int	i;

	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int	num;
	int	neg;
	int	pos;

	num = 0;
	neg = 1;
	pos = number(nptr);
	if (nptr[pos] == '-' || (nptr[pos] == '+'))
	{
		if (nptr[pos] == '-')
			neg *= -1;
		pos++;
	}
	while (nptr[pos])
	{
		if (nptr[pos] >= '0' && nptr[pos] <= '9')
		{
			num = num * 10 + (nptr[pos] - '0');
			pos++;
		}
		else
			break ;
	}
	return (num * neg);
}

/*
int main (void)
{
	const char nptr[] = "b422";
	printf("this is the ft_ funct.: %d\n", ft_atoi(nptr));
	printf("this is the orig. funct.: %d\n", atoi(nptr));
	return 0;
}
*/
/*
int    main(void)
{
	printf("Haben:\n");
	printf("1__ %d\n", ft_atoi("     123"));
	printf("2__ %d\n", ft_atoi("-4123"));
	printf("3__ %d\n", ft_atoi("--4123"));
	printf("4__ %d\n", ft_atoi("---4123"));
	printf("5__ %d\n", ft_atoi("-+-42"));
	printf("6__ %d\n", ft_atoi(" ---+--+1234ab567"));
	printf("6__ %d\n", ft_atoi(" - --+--+1234ab567"));
	printf("7__ %d\n", ft_atoi("b"));
	printf("8__ %d\n", ft_atoi("b42"));
	printf("\n");     printf("Soll:\n");
	printf("1__ %d\n", atoi("     123"));
	printf("2__ %d\n", atoi("-4123"));
	printf("3__ %d\n", atoi("--4123"));
	printf("4__ %d\n", atoi("---4123"));
	printf("5__ %d\n", atoi("-+-42"));
	printf("6__ %d\n", atoi(" ---+--+1234ab567"));
	printf("6__ %d\n", atoi(" - --+--+1234ab567"));
	printf("7__ %d\n", atoi("b"));
	printf("8__ %d\n", atoi("b42"));
}
*/
/*
while (nptr[pos] <= '0' && nptr[pos] >= '9')
{
	num = num * 10 + (nptr[i] - '0');
	pos++;
	i++;
}
*/

/*
The  atoi()  function converts the
initial  portion  of  the   string
pointed  to  by  nptr to int.  The
behavior is the same as

   strtol(nptr, NULL, 10);

except that atoi() does not detect
errors.
*/