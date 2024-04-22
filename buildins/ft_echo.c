/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:20:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 14:22:12 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	check_newline(char *new_line)
{
	int	i;

	i = 1;
	if (!new_line)
		return (0);
	if (new_line[0] != '-')
		return (0);
	if (!new_line[i])
		return (0);
	while (new_line[i])
	{
		if (new_line[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_parse **node, t_mini **mini)
{
	bool	line;
	int		i;
	int		len;

	i = 1;
	len = 0;
	line = true;
	while (check_newline((*node)->command[i]) == 1)
	{
		line = false;
		i++;
	}
	while ((*node)->command[i])
	{
		len = ft_strlen((*node)->command[i]);
		write(1, (*node)->command[i], len);
		if ((*node)->command[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (line == true)
		write(1, "\n", 1);
	(*mini)->exit_status = 0;
	return (0);
}
