/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:02:21 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/22 16:23:00 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libft/libft.h"
#include <unistd.h>

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
{//TODO PROTECTION
	if (i == 0)
	{
		if (comm->infd > 0)
		{
			dup2(comm->infd, STDIN_FILENO);
			//close(comm->infd);
		}
		else
			dup2(STDIN_FILENO, STDIN_FILENO);
		if (comm->outfd > 0)
		{
			dup2(comm->outfd, STDOUT_FILENO);
			//close(comm->outfd);
		}
		else
		{
			// ft_putendl_fd("HERE1", 2);
			// ft_putnbr_fd(i, 2);
			// write(2, "\n", 1);
			dup2(ex_utils->fd[i][1], STDOUT_FILENO);
			//close(ex_utils->fd[i][1]);
		}
	}
	else if (i < ex_utils->pipecount && i > 0)
	{
		if (comm->infd > 0)
		{
			dup2(comm->infd, STDIN_FILENO);
			//close(comm->infd);
			if (comm->outfd > 0)
			{
				dup2(comm->outfd, STDOUT_FILENO);
				//close(comm->outfd);
			}
		}
		else if (comm->outfd > 0)
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			//close(ex_utils->fd[i - 1][0]);
			dup2(comm->outfd, STDOUT_FILENO);
			//close(comm->outfd);
		}
		else
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			//close(ex_utils->fd[i - 1][0]);
			dup2(ex_utils->fd[i][1], STDOUT_FILENO);
			//close(ex_utils->fd[i][1]);
		}
	}
	else if(i == ex_utils->pipecount && i > 0)
	{
		if (comm->infd > 0)
		{
			dup2(comm->infd, STDIN_FILENO);
			//close(comm->infd);
			if (comm->outfd > 0)
			{
				dup2(comm->outfd, STDOUT_FILENO);
				//close(comm->outfd);
			}
		}
		else if (comm->outfd > 0)
		{
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			//close(ex_utils->fd[i - 1][0]);
			dup2(comm->outfd, STDOUT_FILENO);
			//close(comm->outfd);
		}
		else
		{
			// ft_putendl_fd("HERE2", 2);
			// ft_putnbr_fd(i, 2);
			// write(2, "\n", 1);
			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
			//close(ex_utils->fd[i - 1][0]);
			//dup2(STDOUT_FILENO, STDOUT_FILENO);
		}
	}
	return ((void *)1);
}

// void	*dup_filedescriptors(t_parse *comm, t_exe *ex_utils, int i)
// {//TODO PROTECTION
// 	if (i == 0)
// 	{
// 		if (comm->infd > 0)
// 		{
// 			comm->infd = dup(STDIN_FILENO);
// 			close(comm->infd);
// 		}
// 		if (comm->outfd > 0)
// 		{
// 			comm->outfd = dup(STDOUT_FILENO);
// 			close(comm->outfd);
// 		}
// 		else
// 		{
// 			ex_utils->fd[i][1] = dup(STDOUT_FILENO);
// 			close(ex_utils->fd[i][1]);
// 		}			

// 	}
// 	else if (i < ex_utils->pipecount && i > 0)
// 	{
// 		if (comm->infd > 0)
// 		{
// 			comm->infd = dup(STDIN_FILENO);
// 			close(comm->infd);
// 			if (comm->outfd > 0)
// 			{
// 				comm->outfd = dup(STDOUT_FILENO);
// 				close(comm->outfd);
// 			}
// 		}
// 		else if (comm->outfd > 0)
// 		{
// 			ex_utils->fd[i][i - 1] = dup(STDIN_FILENO);
// 			close(ex_utils->fd[i][i - 1]);
// 			comm->outfd = dup(STDOUT_FILENO);
// 			close(comm->outfd);
// 		}
// 		else
// 		{
// 			ex_utils->fd[i - 1][0] = dup(STDIN_FILENO);
// 			close(ex_utils->fd[i - 1][0]);
// 			ex_utils->fd[i][1] = dup(STDOUT_FILENO);
// 			close(ex_utils->fd[i][1]);
// 		}
// 	}
// 	else if(i == ex_utils->pipecount && i > 0)
// 	{
// 		if (comm->infd > 0)
// 		{
// 			comm->infd = dup(STDIN_FILENO);
// 			close(comm->infd);
// 			if (comm->outfd > 0)
// 			{
// 				comm->outfd = dup(STDOUT_FILENO);
// 				close(comm->outfd);
// 			}
// 		}
// 		else if (comm->outfd > 0)
// 		{
// 			ex_utils->fd[i - 1][0] = dup(STDIN_FILENO);
// 			close(ex_utils->fd[i - 1][0]);
// 			comm->outfd = dup(STDOUT_FILENO);
// 			close(comm->outfd);
// 		}
// 		else
// 		{
// 			// ft_putendl_fd("HERE2", 2);
// 			// ft_putnbr_fd(i, 2);
// 			// write(2, "\n", 1);
// 			dup2(ex_utils->fd[i - 1][0], STDIN_FILENO);
// 			ex_utils->fd[i - 1][0] = dup(STDIN_FILENO);
// 			close(ex_utils->fd[i - 1][0]);
// 			//dup2(STDOUT_FILENO, STDOUT_FILENO);
// 		}
// 	}
// 	return ((void *)1);
// }


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
	if(comm)
	{
		if (comm->infd > 0)
			close(comm->infd);
		if (comm->outfd > 0)
			close(comm->outfd);
	}
	return ((void *)1);
}