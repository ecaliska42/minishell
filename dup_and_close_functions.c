/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:17:35 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

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

static int	between_pipe_in(t_parse **comm, t_exe **ex_utils, int i)
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
	return (SUCCESS);
}

static int	between_pipe(t_parse **comm, int i, t_exe **ex_utils)
{
	if ((*comm)->infd > 0)
	{
		if (between_pipe_in(comm, ex_utils, i) == ERROR)
			return (ERROR);
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
