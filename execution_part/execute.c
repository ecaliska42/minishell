/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/23 18:52:41 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
}	t_exe;

//TODO TEMPORARY
int fdprintf ( int fd, const char * fmt, ... )
{
  char * buffer;
  int n;
  va_list ap;

  buffer = ( char * ) malloc (100);
  if ( !buffer )
    return 0;

  va_start ( ap, fmt );
  n = vsnprintf ( buffer, 100, fmt, ap );
  va_end ( ap );

  write ( fd, buffer, n );
  free ( buffer );
  return n;
}

//TODO add closing functions after each dup2
void	child(t_parse *comm, t_exe *ex_utils, int i, t_file *files, int pipes, char **envp)
{
	(void) files;
	if (pipes != 0)
	{
		if (i == 0)
		{
			if(dup2(ex_utils->fd[i][1], STDOUT_FILENO) == -1)
				perror("");
			if (i == pipes)
			{
				if(dup2(ex_utils->fd[i][0], STDIN_FILENO) == -1)
					perror("");
				if(dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
					perror("");
			}
		}
		else if (i < pipes)
		{
			if(dup2(ex_utils->fd[i - 1][0], STDIN_FILENO) == -1)
				perror("");
			if(dup2(ex_utils->fd[i][1], STDOUT_FILENO) == -1)
				perror("");
		}
		if(i == pipes && i > 0)
		{
			if(dup2(ex_utils->fd[i - 1][0], STDIN_FILENO) == -1)
				perror("");
			if(dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
				perror("");
		}
		for (int x = 0; ex_utils->fd[x]; x++)
		{
			if (close(ex_utils->fd[x][1]) == -1)
				perror("loop 1 ");
			if (close(ex_utils->fd[x][0]) == -1)
				perror("loop 2 ");
		}
	}
	//fdprintf(2, "check is %s and command is %s\n", comm->check, comm->command[0]);
	execve(comm->check, comm->command, envp); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
	perror("execve : ");
	write(2, comm->command[0], ft_strlen(comm->command[0]));
	write(2, " : command not found\n", 22);
	exit(127);//TODO look into correct exit status with echo $?
}


int	execute(t_parse **comm, t_mini *count, char **envp)
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
			child(tmp, &ex_struct, i, &files, count->pipecount, envp);
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
