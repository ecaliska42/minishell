/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:00 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 15:38:55 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

static void	close_fds(t_exe **ex_utils)
{
	int	i;

	i = 0;
	while ((*ex_utils)->fd[i])
	{
		if ((*ex_utils)->fd[i][1] > 0)
		{
			if (close((*ex_utils)->fd[i][1]) == -1)
				perror("close filedescriptor error: ");
			(*ex_utils)->fd[i][1] = -1;
		}
		if ((*ex_utils)->fd[i][0] > 0)
		{
			if (close((*ex_utils)->fd[i][0]) == -1)
				perror("close filedescriptor error: ");
			(*ex_utils)->fd[i][0] = -1;
		}
		i++;
	}
}

void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils)
{
	close_fds(&ex_utils);
	while (comm)
	{
		if (comm->infd > 0)
		{
			close(comm->infd);
			(comm->infd) = -1;
		}
		if (comm->outfd > 0)
		{
			close(comm->outfd);
			(comm->outfd) = -1;
		}
		comm = comm->next;
	}
	return ((void *)1);
}
