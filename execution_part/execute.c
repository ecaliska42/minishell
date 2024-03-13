/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/13 18:03:50 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_double(int **fds)
{
	int	i;

	i = 0;
	while(fds[i])
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
	fds = NULL;
}

int		list_size(t_env **envp)
{
	int	i;
	t_env	*tmp;

	i = 0;
	tmp = *envp;	
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_envp(t_env **envp)
{
	t_env	*tmp;
	int	i;

	i = 0;
	tmp = *envp;
	while (tmp)
	{
		printf("name = %s\n", tmp->name);
		while (tmp->values[i])
		{
			printf("values[%d] = %s\n", i, tmp->values[i]);
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}

char	**change_envp(t_env **envp)
{
	int	size = list_size(envp);
	char	**new_envp;
	t_env	*tmp;
	int	i;
	int	j;
	
	i = 0;

	tmp = *envp;
	new_envp = malloc(sizeof(char *) * (size + 1));
	if (!new_envp)
	{
		perror("new_envp malloc error (execute.c) :");
		exit (1);
	}
	new_envp[size] = NULL;
	while (i < size)
	{
		j = 0;
		new_envp[i] = ft_strjoin(tmp->name, "=");
		while(tmp->values[j])
		{
			new_envp[i] = ft_strjoin(new_envp[i], tmp->values[j]);
			if (tmp->values[j + 1])
				new_envp[i] = ft_strjoin(new_envp[i], ":");
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	return (new_envp);
}

void	print_char_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

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
		//write(2, "buildin\n", 8);
		//ft_putendl_fd(comm->command[1], 2);
		execute_buildin(comm->command, envp);
		exit (0);
	}
	else
	{
		//print_envp(envp);
		//printf("\n\n\n");
		//print_char_double(change_envp(envp));
		execve(comm->check, comm->command, change_envp(envp)); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
		//perror("execve : ");
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
	ex_struct.id = malloc((pipecount + 1) * sizeof(pid_t));//TODO FREE
	if (!ex_struct.id)
	{
		perror("ex_struct.id malloc error (execute.c) :");
		exit (1);
	}
	ex_struct.fd = malloc((pipecount + 1) * sizeof(int *) + 1);//TODO FREE DOUBLE
	if (!ex_struct.fd)
	{
		perror("ex_struct.fd malloc error (execute.c) :");
		exit (1);
	}
	ex_struct.pipecount = pipecount;
	i = 0;
	while (i < pipecount)
	{
		ex_struct.fd[i] = malloc(sizeof(int) * 2);
		if (!ex_struct.fd[i])
		{
			perror("ex_struct.fd[i] malloc error (execute.c) :");
			ft_putnbr_fd(i, 2);
			exit (1);
		}
		if (pipe(ex_struct.fd[i]) == -1)
		{
			perror("pipe error (execute.c) :");
			ft_putnbr_fd(i, 2);
			exit (1);
		}
		i++;
	}
	ex_struct.fd[i] = NULL;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->command)
		{
			if (is_parrent_buildin(tmp->command[0]) == true)
				parrent_buildin(tmp->command[0], envp);
			else
			{
				ex_struct.id[i] = fork();
				if (ex_struct.id[i] == -1)
				{
					perror("");
					exit (1);
				}
				if (ex_struct.id[i] == 0)
					child(tmp, &ex_struct, i, envp);
				i++;
			}
		}
		tmp = tmp->next;
	}
	close_filedescriptor(NULL, &ex_struct);
	i--;
	while (i >= 0)
	{
		waitpid(ex_struct.id[i], NULL, 0);
		i--;
	}
	free(ex_struct.id);
	ex_struct.id = NULL;
	free_double(ex_struct.fd);
	return 0;
}
