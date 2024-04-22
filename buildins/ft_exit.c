/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 14:35:14 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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

void	ft_exit(t_parse **node, t_mini **mini)
{
	int		exit_code;

	exit_code = 0;
	if (array_size((*node)->command) == 1)
	{
		write(0, "exit\n", 5);
		exit((*mini)->exit_status);
	}
	if (is_only_numbers((*node)->command[1]) == false
		|| ft_strlen((*node)->command[1]) == 0)
	{
		write(2, "exit\nexit: ", 12);
		write(2, (*node)->command[1], ft_strlen((*node)->command[1]));
		write(2, ": numeric arguments required\n", 29);
		exit (2);
	}
	if (array_size((*node)->command) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		(*mini)->exit_status = 1;
		return ;
	}
	exit_code = (ft_atol((*node)->command[1]) % 256);
	exit (exit_code);
}
