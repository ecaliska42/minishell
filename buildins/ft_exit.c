/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/17 17:16:21 by ecaliska         ###   ########.fr       */
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
	t_parse	*parse;
	int		exit_code;

	parse = *node;
	exit_code = 0;
	if (array_size(parse->command) == 1)
	{
		write(2, "exit\n", 5);
		// printf("exit\n");
		exit((*mini)->exit_status);
	}
	if (is_only_numbers(parse->command[1]) == false || ft_strlen(parse->command[1]) == 0)
	{
		write(2, "exit\n", 5);
		write(2, "exit: ", 7);
		write(2, parse->command[1], ft_strlen(parse->command[1]));
		write(2, ": numeric arguments required\n", 29);
		exit (2);
	}
	if (array_size(parse->command) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		(*mini)->exit_status = 1;
		return ; //TODO SET EXITCODE TO 1
	}
	exit_code = ft_atol(parse->command[1]);
	exit_code = exit_code % 256;
	exit (exit_code);
}
