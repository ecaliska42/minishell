/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/08 18:35:24 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child(t_parse *comm, t_exe *ex_utils, int i, t_env **envp)
{//TODO protection
	if (ex_utils->pipecount != 0)
	{
		dup_filedescriptor(comm, ex_utils, i);
		close_filedescriptor(comm, ex_utils);
	}
	else
		dup_for_no_pipes(comm);
	if (comm->infd < 0)
		exit (1);
	if (is_buildin(comm->command) == true)
	{
		execute_buildin(comm->command[0], envp);
		exit (0);
	}
	else
	{
		// ft_putendl_fd(comm->check, 2);
		// ft_putendl_fd(comm->command[0], 2);
		// ft_putendl_fd(comm->command[1], 2);
		// ft_putendl_fd(comm->command[2], 2);
		execve(comm->check, comm->command, NULL); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
		perror("execve : ");
		write(2, comm->command[0], ft_strlen(comm->command[0]));
		write(2, " : command not found\n", 22);
	}
	exit(127);//TODO look into correct exit status with echo $?
}


int	execute(t_parse **comm, int pipecount, t_env **envp)
{//TODO protection
	t_exe	ex_struct;
	t_parse *tmp;
	int		i;

	tmp = *comm;
	ex_struct.id = malloc(pipecount * sizeof(pid_t));
	ex_struct.fd = malloc(pipecount * sizeof(int *) + 1);
	ex_struct.pipecount = pipecount;
	i = 0;
	while (i < pipecount)
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
		if (ex_struct.id[i] == -1)
		{
			perror("");
			exit (1);
		}
		if (ex_struct.id[i] == 0)
			child(tmp, &ex_struct, i, envp);
		tmp = tmp->next;
		i++;
	}
	close_filedescriptor(NULL, &ex_struct);
	i--;
	while (i >= 0)
	{
		waitpid(ex_struct.id[i], NULL, 0);
		i--;
	}
	return 0;
}
