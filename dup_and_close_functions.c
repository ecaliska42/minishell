/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/28 12:29:59 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

int fail_dup2(int oldfd, int newfd) {
	(void)oldfd;
	(void)newfd;
    return -1;
}

//TODO add closing functions after each dup2

void	*dup_for_no_pipes(t_parse *comm)
{
	if (comm->infd > 0)
	{
		if (dup2(comm->infd, STDIN_FILENO) == -1)
			return (NULL);
		close(comm->infd);
	}
	if (comm->outfd > 0)
	{
		if (dup2(comm->outfd, STDOUT_FILENO) == -1)
			return (NULL);
		close(comm->outfd);
	}
	return ((void *)1);
}

static int	first_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		if (dup2((*comm)->infd, STDIN_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (dup2(STDIN_FILENO, STDIN_FILENO) == -1)
			return (ERROR);
	}
	if ((*comm)->outfd > 0)
	{
		if (dup2((*comm)->outfd, STDOUT_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (dup2((*ex_utils)->fd[i][1], STDOUT_FILENO) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	between_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		if (dup2((*comm)->infd, STDIN_FILENO) == -1)
			return (ERROR);
		if ((*comm)->outfd > 0)
		{
			if (dup2((*comm)->outfd, STDOUT_FILENO) == -1)
				return (ERROR);
		}
		else
		{
			if (dup2((*ex_utils)->fd[i][1], STDOUT_FILENO) == -1)
				return (ERROR);
		}
	}
	else if ((*comm)->outfd > 0)
	{
		if (dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO) == -1)
			return (ERROR);
		if (dup2((*comm)->outfd, STDOUT_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO) == -1)
			return (ERROR);
		if (dup2((*ex_utils)->fd[i][1], STDOUT_FILENO) == -1)
			return (ERROR);
	}
	return (SUCCESS);
}

static int	last_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		if (dup2((*comm)->infd, STDIN_FILENO) == -1)
			return (ERROR);
		if ((*comm)->outfd > 0)
		{
			if (dup2((*comm)->outfd, STDOUT_FILENO) == -1)
				return (ERROR);
		}
	}
	else if ((*comm)->outfd > 0)
	{
		if (dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO) == -1)
			return (ERROR);
		if (dup2((*comm)->outfd, STDOUT_FILENO) == -1)
			return (ERROR);
	}
	else
	{
		if (dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO) == -1)
			return (ERROR);
		// if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
		// 	return (ERROR);
	}
	return (SUCCESS);
}

int	dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i)
{
	if (i == 0)
	{
		if (first_pipe(&comm, i, &ex_utils) == ERROR)
			return (ERROR);
	}
	else if (i < ex_utils->pipecount && i > 0)
	{
		if (between_pipe(&comm, i, &ex_utils) == ERROR)
			return (ERROR);
	}
	else if (i == ex_utils->pipecount && i > 0)
	{
		if (last_pipe(&comm, i, &ex_utils) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
