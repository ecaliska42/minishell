/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/24 16:53:54 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static bool	is_only_numbers(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

void	ft_exit(t_parse **node)
{
	t_parse	*parse;
	int		exit_code;

	parse = *node;
	exit_code = 0;
	if (array_size(parse->command) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		return ;//TODO SET EXITCODE TO 1
	}
	if (is_only_numbers(parse->command[1]) == false)
	{
		write(2, "exit: ", 7);
		write(2, parse->command[1], ft_strlen(parse->command[1]));
		write(2, ": numeric arguments required\n", 29);
		exit (2);
	}
	exit_code = ft_atoi(parse->command[1]);//TODO OVERFLOW MAYBE WITH ATOL
	exit_code = exit_code % 256;
	exit (exit_code);
}
// {
// 	//ft_putendl_fd("IN EXIT", 2);
// 	ft_putstr_fd("exiting\n", 2);
// 	exit(0);
// 	return 0;
// }