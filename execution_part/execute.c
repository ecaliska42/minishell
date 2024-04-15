/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/15 20:41:42 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

// static int	child_files(t_parse **comm)
// {
// 	int	trunc;
// 	int	append;

// 	trunc = O_WRONLY | O_CREAT | O_TRUNC;
// 	append = O_WRONLY | O_CREAT | O_APPEND;
// 	if ((*comm)->infile)
// 	{
// 		if ((*comm)->infile_type == INPUT)
// 			(*comm)->infd = open((*comm)->infile, O_RDONLY);
// 		else if ((*comm)->infile_type == HEREDOC)
// 			heredoc((*comm), (*comm)->infile);
// 		if ((*comm)->infile_type == INPUT && (*comm)->infd == -1)
// 			perror("INFD ERROR1:");
// 	}
// 	if ((*comm)->outfile)
// 	{
// 		if ((*comm)->outfile_type == OUTPUT)
// 			(*comm)->outfd = open((*comm)->outfile, trunc, 0644);
// 		else if ((*comm)->outfile_type == APPEND)
// 			(*comm)->outfd = open((*comm)->outfile, append, 0644);
// 		if ((*comm)->outfd == -1)
// 			perror("OUTFD ERROR1:");
// 	}
// 	return (SUCCESS);
// }


void *dup_filedescriptors(t_parse *comm, t_exe *ex_utils, int i)
{
	if (comm->infd > 0)
	{
		if (dup2(comm->infd, STDIN_FILENO) == -1)
			perror("");
		if (comm->outfd > 0)
		{
			if (dup2(comm->outfd, STDOUT_FILENO) == -1)
				perror("");
		}
		else
		{
			if (dup2(ex_utils->fd[i][1], STDOUT_FILENO) == -1)
				perror("");
			// close (ex_utils->fd[1]);
		}
	}
	else if (comm->outfd > 0)
	{
		if (dup2(ex_utils->fd[i-1][0], STDIN_FILENO) == -1)
			perror("");
		if (dup2(comm->outfd, STDOUT_FILENO) == -1)
			perror("");
	}
	else
	{
		// write(2, "IN ELSE\n", 8);
		if (i == 0)
		{
			// if (dup2(STDIN_FILENO, STDIN_FILENO) == -1)
			// 	perror("");
		}
		else
		{
			if (dup2(ex_utils->fd[i-1][0], STDIN_FILENO) == -1)
				perror("");
			// close (ex_utils->fd[0]);
		}
		if (i == ex_utils->pipecount)
		{
			// write(2, "IN i = pipecount\n", 18);
			// if (dup2(STDOUT_FILENO, STDOUT_FILENO) == -1)
			// 	perror("");
		}
		else
		{
			// write(2, "IN ELSE 2\n", 10);
			if (dup2(ex_utils->fd[i][1], STDOUT_FILENO) == -1)
				perror("");
			// close (ex_utils->fd[1]);
		}
		// dup2(ex_utils->fd[1], STDOUT_FILENO);
		// close (ex_utils->fd[1]);
	}
	return ((void *)1);
}


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
	// close(ex_utils->fd[0]);
	// close(ex_utils->fd[1]);
	if (comm && comm->infd > 0)
		close(comm->infd);
	if (comm && comm->outfd > 0)
		close(comm->outfd);
	return ((void *)1);
}



void	child(t_parse *comm, int i, t_mini **mini)
{
	// child_files(&comm);
	t_mini *ms = *mini;
	if (comm->execute == IGNORE)
		exit(1);
	if (comm->command && (comm->command[0][0] == '/' || (comm->command[0][0] == '.' && comm->command[0][1] == '/')))
	{
		if (opendir(comm->command[0]) != NULL)
		{
			write(2, comm->command[0], ft_strlen(comm->command[0]));
			write(2, ": is a directory\n", 18);
			exit(126);
		}
		if (access(comm->command[0], F_OK) == -1)
		{
			write(2, comm->command[0], ft_strlen(comm->command[0]));
			write(2, ": No such file or directory\n", 28);
			exit(127);
		}
	}
	// ft_putendl_fd("HERE", 2);
	char **envp = change_envp(&ms->env);
	if (ms->exe.pipecount != 0)
	{
		// dup_filedescriptors(comm, &ms->exe, i);
		dup_filedescriptors(comm, &ms->exe, i);
		close_filedescriptor(comm, &ms->exe);
	}
	else
		dup_for_no_pipes(comm);
	if (is_buildin(comm->command) == true)
	{
		execute_buildin(&comm, &ms->env, ms->exe.pipecount, &ms);
		close_filedescriptor(comm, &ms->exe);
		// close(ms->exe.fd[0]);
		// close(ms->exe.fd[1]);
		exit (SUCCESS);
	}
	close_filedescriptor(comm, &ms->exe);
	execve(comm->check, comm->command, envp);
	write(2, comm->command[0], ft_strlen(comm->command[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

int	execute(t_mini **mini)//(t_parse **comm, int pipecount, t_env **envp)
{
	// t_exe	ex_struct;
	t_parse	*parse;
	int		i;

	parse = (*mini)->parse;
	if (malloc_ex_struct(&(*mini)->exe) == ERROR)
		return (ERROR);
	// ft_putnbr_fd((*mini)->exe.pipecount, 2);
	// write(2, "\n", 1);
	if (is_buildin(parse->command) == true && (*mini)->exe.pipecount == 0)
	{
		lonely_buildin(parse, &(*mini)->env, mini);
		free((*mini)->exe.id);
		(*mini)->exe.id = NULL;
		// free_fds((*mini)->exe.fd);
		return (SUCCESS);
	}
	if (create_pipes(&(*mini)->exe) == ERROR)
		return (ERROR);
	i = 0;
	while (parse != NULL)
	{
		if (pipe((*mini)->exe.fd[i]) == -1)
		{
			perror("PIPE ERROR:");
			return (ERROR);
		}
		(*mini)->exe.id[i] = fork();
		if ((*mini)->exe.id[i] == -1)
		{
			perror("FORK ERROR:");
			return (ERROR);
		}
		if ((*mini)->exe.id[i] == 0)
		{
			signal_handler(2);
			child(parse, i, mini);
			// close((*mini)->exe.fd[0]);
			// close((*mini)->exe.fd[1]);
		}
		// close((*mini)->exe.fd[i][1]);
		i++;
		parse = parse->next;
	}
	close_filedescriptor(NULL, &(*mini)->exe);
	// close((*mini)->exe.fd[1]);
	// close((*mini)->exe.fd[0]);
	i--;
	while (i >= 0)
	{
		waitpid((*mini)->exe.id[i], &(*mini)->exit_status, 0);
		i--;
	}
	if(WIFEXITED((*mini)->exit_status))
		(*mini)->exit_status = WEXITSTATUS((*mini)->exit_status);
	else if(WIFSIGNALED((*mini)->exit_status))
		(*mini)->exit_status = 128 + WTERMSIG((*mini)->exit_status);
	free((*mini)->exe.id);
	(*mini)->exe.id = NULL;
	free_fds((*mini)->exe.fd);
	return (SUCCESS);
}
