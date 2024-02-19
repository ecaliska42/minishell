/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/19 16:58:49 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
}	t_exe;

void	child(t_parse *comm, t_exe *ex_utils, int i, t_file *files, int pipes)
{
	if (i == 0)
	{
		dup2(files->infile, STDIN_FILENO);
		close(files->infile);
		dup2(ex_utils->fd[i][1], ex_utils->fd[i+1][0]);
		close(ex_utils->fd[i][1]);
	}
	else if (i > 0 && i < pipes)
	{
		dup2(ex_utils->fd[i][0], ex_utils->fd[i - 1][1]);
		close(ex_utils->fd[i][0]);
		dup2(ex_utils->fd[i][1], ex_utils->fd[i + 1][0]);
		close(ex_utils->fd[i][1]);
	}
	if(i == pipes)
	{
		dup2(ex_utils->fd[i][0], ex_utils->fd[i-1][1]);
		close(ex_utils->fd[i][0]);
		dup2(ex_utils->fd[i][1], files->outfile);
		close(ex_utils->fd[i][1]);
	}
	execve(comm->check, comm->command, NULL); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
}


int	execute(t_parse **comm, t_mini *count)
{
	t_exe	ex_struct;
	t_file	files;
	files.infile = open("infile.txt", O_RDONLY);
	if (files.infile < 0)
		perror("");
	files.outfile = open("outfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files.outfile < 0)
		perror("");
	t_parse *tmp;
	tmp = *comm;
	ex_struct.id = malloc(count->pipecount * sizeof(pid_t));
	ex_struct.fd = malloc(count->pipecount * sizeof(int *) + 1);
	int i = 0;
	while (i <= count->pipecount)
	{
		ex_struct.fd[i] = malloc(sizeof(int) * 2);
		pipe(ex_struct.fd[i]);
		i++;
	}
	i = 0;
	while (tmp != NULL)
	{
	 	//printf("ok\n");
		ex_struct.id[i] = fork();
		if (ex_struct.id[i] == 0)
			child(tmp, &ex_struct, i, &files, count->pipecount);
		tmp = tmp->next;
		i++;
	}
	return 0;
}
