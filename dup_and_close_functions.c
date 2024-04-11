/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/11 17:10:01 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

//TODO add closing functions after each dup2

void	*dup_for_no_pipes(t_parse *comm)
{//TODO PROTECTION
	//ft_putstr_fd("no pipes\n", 2);
	if (comm->infd > 0)
	{
		//ft_putstr_fd("infd > 0\n", 2);
		dup2(comm->infd, STDIN_FILENO);
		close(comm->infd);
	}
	if (comm->outfd > 0)
	{
		//ft_putstr_fd("outfd > 0\n", 2);
		dup2(comm->outfd, STDOUT_FILENO);
		close(comm->outfd);
	}
	return ((void *)1);
}

void	*dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i)
{
	if (i == 0)
	{
		if (comm->infd > 0)
			dup2(comm->infd, STDIN_FILENO);
		else
			dup2(STDIN_FILENO, STDIN_FILENO);
		if (comm->outfd > 0)
			dup2(comm->outfd, STDOUT_FILENO);
		else
			dup2(ex_utils->fd[i][1], STDOUT_FILENO);
	}
	else if (i < ex_utils->pipecount && i > 0)
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
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
	}
	return ((void *)1);
}


void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils)
{//TODO PROTECTION
	int	i;

	i = 0;
	while(ex_utils->fd[i])
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
