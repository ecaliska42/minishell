/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/25 16:22:08 by mesenyur         ###   ########.fr       */
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
	if (array_size((*node)->command) == 1)
	{
		write(0, "exit\n", 5);
		free_mini_and_exit(mini);
	}
	if (is_only_numbers((*node)->command[1]) == false
		|| ft_strlen((*node)->command[1]) == 0)
	{
		write(2, "exit\nexit: ", 12);
		write(2, (*node)->command[1], ft_strlen((*node)->command[1]));
		write(2, ": numeric arguments required\n", 29);
		(*mini)->exit_status = 2;
		free_mini_and_exit(mini);
	}
	if (array_size((*node)->command) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		(*mini)->exit_status = 1;
		return ;
	}
	(*mini)->exit_status = (ft_atol((*node)->command[1]) % 256);
	free_mini_and_exit(mini);
}
