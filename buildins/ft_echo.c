/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:20:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/20 17:57:49 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <stdbool.h>
#include <unistd.h>

int	check_newline(char *new_line)
{
	int	i;

	i = 1;
	if (!new_line)
		return (0);
	if (new_line[0] != '-')
		return (0);
	while (new_line[i])
	{
		if (new_line[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// ft_putendl_fd("IN ECHO", 2);

int	ft_echo(t_token **head)
{
	t_token	*temp;
	bool	line;

	temp = (*head)->next;
	line = true;
	if (!temp || temp->type != RANDOM)
	{
		printf("\n");
		return (0);
	}
	while (check_newline(temp->str) == 1)
	{
		line = false;
		temp = temp->next;
	}
	while (temp != NULL && temp->type == RANDOM)
	{
		printf("%s", temp->str);
		//ft_putstr_fd(temp->str, 1);
		if (temp->next && temp->next->type == RANDOM)
			printf(" ");//ft_putstr_fd(" ", 1);
		temp = temp->next;
	}
	if (line == true)
		printf("\n");
	write(1, "\n", 1);
	return (0);
}
