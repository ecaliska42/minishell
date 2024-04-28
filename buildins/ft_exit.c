/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/27 17:13:11 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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
