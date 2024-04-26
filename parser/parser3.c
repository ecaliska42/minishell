/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:14:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 17:57:09 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_parsing_node(t_parse **head)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head)->next;
		while (tmp->command && tmp->command[i])
		{
			free_and_null((void **)&tmp->command[i]);
			i++;
		}
		i = 0;
		free_and_null((void **)&tmp->check);
		free_and_null((void **)&tmp->command);
		free_and_null((void **)&tmp);
	}
}

int	is_input(char *name, t_parse ****node, t_mini **mini)
{
	if ((***node)->infd != 0)
		close((***node)->infd);
	(***node)->infd = open(name, O_RDONLY);
	if ((***node)->infd == -1)
	{
		(***node)->execute = IGNORE;
		ft_putstr_fd(name, 2);
		write (2, ": ", 2);
		perror("");
		(*mini)->exit_status = 1;
	}
	return (SUCCESS);
}

int	is_output(t_token *tmp, t_parse ****node)
{
	if (tmp->ambiguous == true || tmp->empty == true)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		(***node)->execute = IGNORE;
	}
	else
	{
		if ((***node)->outfd != 0)
			close((***node)->outfd);
		(***node)->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((***node)->outfd == -1)
		{
			perror("");
			(***node)->execute = IGNORE;
		}
	}
	return (SUCCESS);
}

int	is_append(t_token *tmp, t_parse ****node)
{
	if (tmp->ambiguous == true || tmp->empty == true)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		(***node)->execute = IGNORE;
	}
	else
	{
		if ((***node)->outfd != 0)
			close((***node)->outfd);
		(***node)->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((***node)->outfd == -1)
		{
			perror("");
			(***node)->execute = IGNORE;
		}
	}
	return (SUCCESS);
}

int	is_random(t_token *tmp, t_parse ***node)
{
	if (tmp->empty == true)
		(**node)->empty = true;
	if (tmp->empty == false)
		(**node)->empty = false;
	(**node)->command = create_command(tmp->str, (**node)->command);
	if (!(**node)->command)
		return (ERROR);
	return (SUCCESS);
}
