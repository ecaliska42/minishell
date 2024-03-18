/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/18 21:22:26 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <unistd.h>

void	free_fds(int **fds)
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

char	**change_envp(t_env **envp)
{//TODO malloc coorectly at the beginning so i just have to go in this function only once
	int	size = t_env_size(envp);
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
			new_envp[i] = ft_strjoin(new_envp[i], tmp->values);
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	return (new_envp);
}

void	child(t_parse *comm, t_exe *ex_utils, int i, t_env **envp, t_token **token)
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
		execute_buildin(comm->command, envp, token);
		exit(0);
	}
	else
	{
		execve(comm->check, comm->command, change_envp(envp)); //TODO 1: PATH WITH COMMAND ATTATCHED 2: command split with ' '
		//perror("execve : ");
		write(2, comm->command[0], ft_strlen(comm->command[0]));
		write(2, " : command not found\n", 22);
	}
	exit(127);//TODO look into correct exit status with echo $?
}

static int malloc_ex_struct(t_exe *ex_struct, int pipecount)
{
	ex_struct->id = malloc((pipecount + 1) * sizeof(pid_t));//TODO FREE
	if (!ex_struct->id)
	{
		perror("ex_struct.id malloc error (execute.c) :");
		return (ERROR);
	}
	ex_struct->fd = malloc((pipecount + 1) * sizeof(int *) + 1);//TODO FREE DOUBLE
	if (!ex_struct->fd)
	{
		free(ex_struct->id);
		ex_struct->id = NULL;
		perror("ex_struct.fd malloc error (execute.c) :");
		return (ERROR);
	}
	ex_struct->pipecount = pipecount;
	return (SUCCESS);
}

static int create_pipes(t_exe *ex_struct)
{
	int	i;

	i = 0;
	while (i < ex_struct->pipecount)
	{
		ex_struct->fd[i] = malloc(sizeof(int) * 2);
		if (!ex_struct->fd[i])
		{
			perror("ex_struct.fd[i] malloc error (execute.c) : ");
			ft_putnbr_fd(i, 2);
			return (ERROR);
		}
		if (pipe(ex_struct->fd[i]) == -1)
		{
			perror("pipe error (execute.c) : ");
			ft_putnbr_fd(i, 2);
			return (ERROR);
		}
		i++;
	}
	ex_struct->fd[i] = NULL;
	return (SUCCESS);
}

int	execute(t_parse **comm, int pipecount, t_env **envp, t_token **tokens)
{//TODO protection
	t_exe	ex_struct;
	t_parse *parse;
	t_token *token;
	int		i;

	if (malloc_ex_struct(&ex_struct, pipecount) == ERROR)
		return (ERROR);
	if (create_pipes(&ex_struct) == ERROR)
		return (ERROR);//TODO CORRECT PROTECTION
	i = 0;
	parse = *comm;
	token = *tokens;
	while (parse != NULL)
	{
		if (is_buildin(parse->command) == true && pipecount == 0)
		{
			int orig_stdout = dup(1);
			int orig_stdin = dup(0);
			if (parse->infd > 0)
			{
				dup2(parse->infd, STDIN_FILENO);
				close(parse->infd);
				parse->infd = -1;
				dup2(orig_stdin, STDIN_FILENO);
				close (orig_stdin);
			}
			if (parse->outfd > 0)
			{
				dup2(parse->outfd, STDOUT_FILENO);
				close(parse->outfd);
				parse->outfd = -1;
				dup2(orig_stdout, STDOUT_FILENO);
				close (orig_stdout);
			}
			execute_buildin(parse->command, envp, &token);
		}
		else
		{
			ex_struct.id[i] = fork();
			if (ex_struct.id[i] == -1)
			{
				perror("");
				exit (1);//TODO CORRECT PROTECTION
			}
			if (ex_struct.id[i] == 0)
				child(parse, &ex_struct, i, envp, &token);
			i++;
		}
		parse = parse->next;
	}
	close_filedescriptor(NULL, &ex_struct);
	i--;
	while (i >= 0)
		waitpid(ex_struct.id[i--], NULL, 0);
	free(ex_struct.id);
	ex_struct.id = NULL;
	free_fds(ex_struct.fd);
	return 0;
}
