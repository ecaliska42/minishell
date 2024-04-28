/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:00 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/28 12:42:31 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils)
{
	int	i;

	i = 0;
	while (ex_utils->fd[i])
	{
		if (ex_utils->fd[i][1] > 0)
		{
			if (close(ex_utils->fd[i][1]) == -1)
				perror("close filedescriptor error: ");
			ex_utils->fd[i][1] = -1;
		}
		if (ex_utils->fd[i][0] > 0)
		{
			if (close(ex_utils->fd[i][0]) == -1)
				perror("close filedescriptor error: ");
			ex_utils->fd[i][0] = -1;
		}
		i++;
	}
	while (comm)
	{
		if (comm && comm->infd > 0)
		{
			close(comm->infd);
			(comm->infd) = -1;
		}
		if (comm && comm->outfd > 0)
		{
			close(comm->outfd);
			(comm->outfd) = -1;
		}
		comm = comm->next;
	}
	return ((void *)1);
}
