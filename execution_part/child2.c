/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:29:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/03 13:38:27 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	check_dir(char *command, t_mini **mini)
{
	DIR	*dir;

	dir = opendir(command);
	if (dir != NULL)
	{
		write(2, command, ft_strlen(command));
		write(2, ": is a directory\n", 18);
		closedir(dir);
		(*mini)->exit_status = 126;
		free_mini_and_exit(mini);
	}
}

void	print_command_not_found(char **command, t_mini **mini)
{
	while (*command && **command == '\0')
		command++;
	write(2, *command, ft_strlen(*command));
	write(2, ": command not found\n", 21);
	(*mini)->exit_status = 127;
}

void	print_correct_error_message(t_parse *comm, t_mini **mini)
{
	DIR	*dir;

	dir = opendir(comm->command[0]);
	if (dir != NULL && ft_strcmp("..", comm->command[0]) != 0)
	{
		write(2, comm->command[0], ft_strlen(comm->command[0]));
		write(2, ": is a directory\n", 18);
		(*mini)->exit_status = 126;
		closedir(dir);
		return ;
	}
	if (dir != NULL)
		closedir(dir);
	if (comm->empty == false || comm->command[0][0] != '\0')
		return (print_command_not_found(comm->command, mini));
}
