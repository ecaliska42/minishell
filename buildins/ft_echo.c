/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:20:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/28 17:34:51 by ecaliska         ###   ########.fr       */
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
		return (2);
	while (new_line[i])
	{
		if (new_line[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// ft_putendl_fd("IN ECHO", 2);
	// ft_putendl_fd(temp->str, 2);
	// for (int i = 0; parse->command[i]; i++)
	// {
	// 	ft_putendl_fd(parse->command[i], 2);
	// }
	// write(2, "IN ECHO HAHA\n", 13);
	// // write(2, "\n\n\n\n\n", 5);
	// write(2, "\n", 1);
	// for (int i = 0; parse->command[i]; i++)
	// {
	// 	write(2, parse->command[i], strlen(parse->command[i]));
	// 	write(2, "\n", 1);
	// }

// static int	ft_echo_nofd(t_token **head, t_parse **node)
// {
// 	//t_token	*temp;
// 	bool	line;
// 	t_parse	*parse;

// 	(*head) = (*head)->next;
// 	line = true;
// 	parse = *node;
// 	if (!(*head) || (*head)->type != RANDOM)
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	while (check_newline((*head)->str) == 1)
// 	{
// 		line = false;
// 		(*head) = (*head)->next;
// 	}
// 	while ((*head) != NULL && (*head)->type == RANDOM)
// 	{
// 		printf("%s", (*head)->str);
// 		fflush(stdout);
// 		if ((*head)->next && (*head)->next->type == RANDOM)
// 			printf(" ");
// 		(*head) = (*head)->next;
// 	}
// 	if (line == true)
// 		printf("\n");
// 	fflush(stdout);
// 	return (0);
// }

// static int	ft_echo_nofd(t_token **head, t_parse **node)
// {
// 	//t_token	*temp;
// 	bool	line;
// 	t_parse	*parse;

// 	(*head) = (*head)->next;
// 	line = true;
// 	parse = *node;
// 	dprintf(2, "command is %s\n", (*head)->str);
// 	if (!(*head) || (*head)->type != RANDOM)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	while (check_newline((*head)->str) == 1)
// 	{
// 		line = false;
// 		(*head) = (*head)->next;
// 	}
// 	while ((*head) != NULL && (*head)->type == RANDOM)
// 	{
// 		write(1, (*head)->str, strlen((*head)->str));
// 		if ((*head)->next && (*head)->next->type == RANDOM)
// 			write(1, " ", 1);
// 		(*head) = (*head)->next;
// 	}
// 	if (line == true)
// 		write(1, "\n", 1);
// 	return (0);
// }

// static int	ft_echo_nofd(t_token **head, t_parse **node)
// {
// 	t_token	*temp;
// 	bool	line;
// 	t_parse	*parse;

// 	temp = (*head)->next;
// 	line = true;
// 	parse = *node;
// 	if (!temp || temp->type != RANDOM)
// 	{
// 		printf("\n");
// 		return (0);
// 	}
// 	while (check_newline(temp->str) == 1)
// 	{
// 		line = false;
// 		temp = temp->next;
// 	}
// 	while (temp != NULL && temp->type == RANDOM)
// 	{
// 		printf("%s", temp->str);
// 		if (temp->next && temp->next->type == RANDOM)
// 			printf(" ");
// 		temp = temp->next;
// 	}
// 	if (line == true)
// 		printf("\n");
// 	return (0);
// }

// int	ft_echo(t_token ****head, t_parse **node)
// {
// 	//ft_echo_nofd(head, node);
// 	//t_token	*temp;
// 	bool	line;
// 	t_parse	*parse;

// 	(***head) = (***head)->next;
// 	line = true;
// 	parse = *node;
// 	dprintf(2, "command is %s\n", (***head)->str);
// 	if (!(***head) || (***head)->type != RANDOM)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	while (check_newline((***head)->str) == 1)
// 	{
// 		line = false;
// 		(***head) = (***head)->next;
// 	}
// 	while ((***head) != NULL && (***head)->type == RANDOM)
// 	{
// 		write(1, (***head)->str, strlen((***head)->str));
// 		if ((***head)->next && (***head)->next->type == RANDOM)
// 			write(1, " ", 1);
// 		(***head) = (***head)->next;
// 	}
// 	if (line == true)
// 		write(1, "\n", 1);
// 	return (0);
// }

int	ft_echo(t_token **head, t_parse **node)
{
	bool	line;
	int		i;
	int		len;

	i = 1;
	len = 0;
	line = true;
	if (!(*head))
		return (write(1, "\n", 1));
	while (check_newline((*node)->command[i]) != 0)
	{
		if (check_newline((*node)->command[i])==1)
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
	return (0);
}
