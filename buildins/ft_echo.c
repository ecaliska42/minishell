/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:20:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/18 19:49:51 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <stdbool.h>

int	check_newline(char *new_line)
{
	int	i;

	i = 1;
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

	//ft_putendl_fd("IN ECHO", 2);

int	ft_echo(char *new_line, t_token **head)
{
	t_token	*temp;
	bool	line;

	temp = *head;
	temp = temp->next;
	if (!temp || temp->type != RANDOM)
	{
		printf("\n");
		return (0);
	}
	if (check_newline(new_line) == 1)
	{
		line = false;
		temp = temp->next;
	}
	else
		line = true;
	while (temp != NULL && temp->type == RANDOM)
	{
		printf("%s", temp->str);
		if (temp->next)
			printf(" ");
		temp = temp->next;
	}
	if (line == true)
		printf("\n");
	return (0);
}
