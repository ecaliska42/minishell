/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 16:27:04 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

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
		dup2((*comm)->infd, STDIN_FILENO);
	else
		dup2(STDIN_FILENO, STDIN_FILENO);
	if ((*comm)->outfd > 0)
		dup2((*comm)->outfd, STDOUT_FILENO);
	else
		dup2((*ex_utils)->fd[i][1], STDOUT_FILENO);
	return (SUCCESS);
}

static int	between_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		dup2((*comm)->infd, STDIN_FILENO);
		if ((*comm)->outfd > 0)
			dup2((*comm)->outfd, STDOUT_FILENO);
		else
			dup2((*ex_utils)->fd[i][1], STDOUT_FILENO);
	}
	else if ((*comm)->outfd > 0)
	{
		dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO);
		dup2((*comm)->outfd, STDOUT_FILENO);
	}
	else
	{
		dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO);
		dup2((*ex_utils)->fd[i][1], STDOUT_FILENO);
	}
	return (SUCCESS);
}

static int	last_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		dup2((*comm)->infd, STDIN_FILENO);
		if ((*comm)->outfd > 0)
			dup2((*comm)->outfd, STDOUT_FILENO);
	}
	else if ((*comm)->outfd > 0)
	{
		dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO);
		dup2((*comm)->outfd, STDOUT_FILENO);
	}
	else
	{
		dup2((*ex_utils)->fd[i - 1][0], STDIN_FILENO);
		dup2(STDOUT_FILENO, STDOUT_FILENO);
	}
	return (SUCCESS);
}

void	*dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i)
{
	if (i == 0)
	{
		first_pipe(&comm, i, &ex_utils);
	}
	else if (i < ex_utils->pipecount && i > 0)
	{
		between_pipe(&comm, i, &ex_utils);
	}
	else if (i == ex_utils->pipecount && i > 0)
	{
		last_pipe(&comm, i, &ex_utils);
	}
	return ((void *)1);
}
