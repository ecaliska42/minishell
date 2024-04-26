/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:08:00 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 17:43:13 by ecaliska         ###   ########.fr       */
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
	if (comm && comm->infd > 0)
		close(comm->infd);
	if (comm && comm->outfd > 0)
		close(comm->outfd);
	return ((void *)1);
}
