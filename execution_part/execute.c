/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/15 18:22:22 by ecaliska         ###   ########.fr       */
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

void	child(t_parse *comm, int i, t_mini **mini)
{
	// child_files(&comm);
	(void)i;
	t_mini *ms = *mini;
	if (comm->execute == IGNORE)
		exit(1);
	if (comm->command[0][0] == '/' || (comm->command[0][0] == '.' && comm->command[0][1] == '/'))
	{
		if (opendir(comm->command[0]) != NULL)
		{
			// perror("minishell: ");
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
	pipe((*mini)->exe.fd);
	char **envp = change_envp(&ms->env);
	if (ms->exe.pipecount != 0)
	{
		// dup_filedescriptors(comm, &ms->exe, i);
		dup_filedescriptors(comm, &ms->exe);
		// close_filedescriptor(comm, &ms->exe);
	}
	else
		dup_for_no_pipes(comm);
	if (is_buildin(comm->command) == true)
	{
		execute_buildin(&comm, &ms->env, ms->exe.pipecount, &ms);
		//close_filedescriptor(comm, ex_utils);
		exit (SUCCESS);
	}
	// close_filedescriptor(comm, &ms->exe);
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
	if (is_buildin(parse->command) == true && (*mini)->exe.pipecount == 0)
	{
		lonely_buildin(parse, &(*mini)->env, mini);
		free((*mini)->exe.id);
		(*mini)->exe.id = NULL;
		// free_fds((*mini)->exe.fd);
		return (SUCCESS);
	}
	// if (create_pipes(&(*mini)->exe) == ERROR)
	// 	return (ERROR);
	i = 0;
	while (parse != NULL)
	{
		// pipe((*mini)->exe.fd);
		(*mini)->exe.id[i] = fork();
		if ((*mini)->exe.id[i] == 0)
		{
			signal_handler(2);
			child(parse, i, mini);
		}
		// close((*mini)->exe.fd[1]);
		// close((*mini)->exe.fd[0]);
		i++;
		parse = parse->next;
	}
	close_filedescriptor(NULL, &(*mini)->exe);
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
	// free_fds((*mini)->exe.fd);
	return (SUCCESS);
}
