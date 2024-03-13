/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/12 14:11:13 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

//TODO add closing functions after each dup2

void	*dup_for_no_pipes(t_parse *comm)
{//TODO PROTECTION
	if (comm->infd > 0)
	{
		dup2(comm->infd, STDIN_FILENO);
		close(comm->infd);
	}
	if (comm->outfd > 0)
	{
		dup2(comm->outfd, STDOUT_FILENO);
		close(comm->outfd);
	}
	return ((void *)1);
}

void	*dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i)
{//TODO PROTECTION
	if (i == 0)
	{
		if (comm->infd > 0)
			dup2(comm->infd, STDIN_FILENO);
		if (comm->outfd > 0)
			dup2(comm->outfd, STDOUT_FILENO);
		else
			dup2(ex_utils->fd[i][1], STDOUT_FILENO);
	}
	else if (i < ex_utils->pipecount)
	{
		if (comm->infd > 0)
		{
			dup2(comm->infd, STDIN_FILENO);
			if (comm->outfd > 0)
				dup2(comm->outfd, STDOUT_FILENO);
		}
		else if (comm->outfd > 0)
		{
			dup2(ex_utils->fd[i][0], STDIN_FILENO);
			dup2(comm->outfd, STDOUT_FILENO);
		}
		else
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			dup2(ex_utils->fd[i][1], STDOUT_FILENO);
		}
	}
	else if(i == ex_utils->pipecount && i > 0)
	{
		if (comm->infd > 0)
		{
			dup2(comm->infd, STDIN_FILENO);
			if (comm->outfd > 0)
				dup2(comm->outfd, STDOUT_FILENO);
		}
		else if (comm->outfd > 0)
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			dup2(comm->outfd, STDOUT_FILENO);
		}
		else
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			dup2(STDOUT_FILENO, STDOUT_FILENO);
		}
	}
	return ((void *)1);
}

void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils)
{//TODO PROTECTION
	int	i;

	i = 0;
	while(ex_utils->fd[i])
	{
		if (close(ex_utils->fd[i][1]) == -1)
			perror("");
		if (close(ex_utils->fd[i][0]) == -1)
			perror("");
		i++;
	}
	if(comm)
	{
		if (comm->infd > 0)
			close(comm->infd);
		if (comm->outfd > 0)
			close(comm->outfd);
	}
	return ((void *)1);
}