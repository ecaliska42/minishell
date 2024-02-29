/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/28 18:41:52 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
}	t_exe;

//TODO TEMPORARY
int fdprintf ( int fd, const char * str, ... )
{
  char * buffer;
  int n;
  va_list ap;

  buffer = ( char * ) malloc (100);
  if ( !buffer )
    return 0;

  va_start ( ap, str );
  n = vsnprintf ( buffer, 100, str, ap );
  va_end ( ap );

  write ( fd, buffer, n );
  free ( buffer );
  return n;
}

//TODO add closing functions after each dup2
void	child(t_parse *comm, t_exe *ex_utils, int i, int pipes, t_env **envp)
{
	if (pipes != 0)
	{
		if (i == 0)
		{
			ft_putstr_fd(comm->infile, 2);
			write(2, "\n", 2);
			if (comm->infd > 0 && comm->infile)
				dup2(comm->infd, STDIN_FILENO);
			if (comm->outfd > 0 && comm->outfile)
				dup2(comm->outfd, STDOUT_FILENO);
			else
				dup2(ex_utils->fd[i][1], STDOUT_FILENO);
		}
		else if (i < pipes)
		{
			if (comm->infd > 0 && comm->infile)
			{
				dup2(comm->infd, STDIN_FILENO);
				if (comm->outfd > 0 && comm->outfile)
					dup2(comm->outfd, STDOUT_FILENO);
			}
			else if (comm->outfd > 0 && comm->outfile)
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
		else if(i == pipes && i > 0)
		{
			if (comm->infd > 0 && comm->infile)
			{
				dup2(comm->infd, STDIN_FILENO);
				if (comm->outfd > 0 && comm->outfile)
					dup2(comm->outfd, STDOUT_FILENO);
			}
			else if (comm->outfd > 0 && comm->outfile)
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
		for (int x = 0; ex_utils->fd[x]; x++)
		{
			if (close(ex_utils->fd[x][1]) == -1)
				perror("loop 1 ");
			if (close(ex_utils->fd[x][0]) == -1)
				perror("loop 2 ");
		}
		if (comm->infd > 0 && comm -> infile)
			close(comm->infd);
		if (comm->outfd > 0 && comm -> outfile)
			close(comm->outfd);
	}
	else
	{
		if (comm->infd > 0 && comm->infile)
		{
			dup2(comm->infd, STDIN_FILENO);
				perror("dup2 l: 153 ");
			close(comm->infd);
				perror("dup2 l: 155 ");
		}
		if (comm->outfd > 0 && comm->outfile)
		{
			if (dup2(comm->outfd, STDOUT_FILENO) == -1)
				perror("dup2 l: 160 ");
			if (close(comm->outfd) == -1)
				perror("dup2 l: 162 ");
		}
	}
	if (comm->infd < 0)
		exit (1);
	if (is_buildin(comm->command, envp) == true)
		execute_buildin(comm->command[0], envp);
	else
		execve(comm->check, comm->command, NULL); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
	perror("execve : ");
	write(2, comm->command[0], ft_strlen(comm->command[0]));
	write(2, " : command not found\n", 22);
	exit(127);//TODO look into correct exit status with echo $?
}

//TODO TEMPOROARY
/*
if (comm->infd > 0 && comm->infile)
{
	if (dup2(comm->infd, STDIN_FILENO) == -1)
		perror("");
	if (close(comm->infd) == -1)
		perror("");
	if (comm->outfd < 0)
	{
		if(dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
			perror("");
	}
}
if (comm->outfd > 0 && comm->outfile)
{
	if (dup2(comm->outfd, STDOUT_FILENO) == -1)
		perror("");
	if (close(comm->outfd) == -1)
		perror("");
	// if(dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
	// 	perror("");
}
*/
//TODO TEMPOROARY END

int	execute(t_parse **comm, t_mini *count, t_env **envp)
{
	t_exe	ex_struct;
	t_parse *tmp;
	tmp = *comm;
	ex_struct.id = malloc(count->pipecount * sizeof(pid_t));
	ex_struct.fd = malloc(count->pipecount * sizeof(int *) + 1);
	int i = 0;
	while (i < count->pipecount)
	{
		ex_struct.fd[i] = malloc(sizeof(int) * 2);
		pipe(ex_struct.fd[i]);
		i++;
	}
	ex_struct.fd[i] = NULL;
	i = 0;
	while (tmp != NULL)
	{
		ex_struct.id[i] = fork();
		if (ex_struct.id[i] == 0)
			child(tmp, &ex_struct, i, count->pipecount, envp);
		tmp = tmp->next;
		i++;
	}
	for (int x = 0; ex_struct.fd[x]; x++)
	{
		close(ex_struct.fd[x][1]);
		close(ex_struct.fd[x][0]);
	}
	i--;
	while (i >= 0)
	{
		waitpid(ex_struct.id[i], NULL, 0);
		i--;
	}
	return 0;
}
