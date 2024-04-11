/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/11 16:12:46 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	ft_exit(t_parse **node)
{
	t_parse	*parse;
	int		exit_code;

	parse = *node;
	exit_code = 0;
	if (array_size(parse->command) == 1)
		exit(0); //exit with last exit code & print exit
	if (array_size(parse->command) > 2)
	{
		write(2, "exit\nexit: too many arguments\n", 31);
		return ; //TODO SET EXITCODE TO 1
	}
	if (is_only_numbers(parse->command[1]) == false || ft_strlen(parse->command[1]) == 0)
	{
		write(2, "exit: ", 7);
		write(2, parse->command[1], ft_strlen(parse->command[1]));
		write(2, ": numeric arguments required\n", 29);
		exit (2);
	}
	exit_code = ft_atol(parse->command[1]);
	exit_code = exit_code % 256;
	exit (exit_code);
}
