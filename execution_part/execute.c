/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/10 17:20:08 by ecaliska         ###   ########.fr       */
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

void	child(t_parse *comm, t_exe *ex_utils, int i, t_env **envp)
{
	// child_files(&comm);
	if (ex_utils->pipecount != 0)
	{
		dup_filedescriptor(comm, ex_utils, i);
		close_filedescriptor(comm, ex_utils);
	}
	else
		dup_for_no_pipes(comm);
	if (is_buildin(comm->command) == true)
	{
		execute_buildin(&comm, envp, ex_utils->pipecount);
		//close_filedescriptor(comm, ex_utils);
		exit (SUCCESS);
	}
	close_filedescriptor(comm, ex_utils);
	execve(comm->check, comm->command, change_envp(envp));
	write(2, comm->command[0], ft_strlen(comm->command[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

int	execute(t_parse **comm, int pipecount, t_env **envp)
{
	t_exe	ex_struct;
	t_parse	*parse;
	int		i;

	parse = *comm;
	if (malloc_ex_struct(&ex_struct, pipecount) == ERROR)
		return (ERROR);
	if (is_buildin(parse->command) == true && pipecount == 0)
	{
		lonely_buildin(parse, envp);
		free(ex_struct.id);
		ex_struct.id = NULL;
		free_fds(ex_struct.fd);
		return (SUCCESS);
	}
	if (create_pipes(&ex_struct) == ERROR)
		return (ERROR);
	i = 0;
	while (parse != NULL)
	{
		ex_struct.id[i] = fork();
		if (ex_struct.id[i] == 0)
		{
			signal_handler(2);
			child(parse, &ex_struct, i, envp);
		}
		i++;
		parse = parse->next;
	}
	close_filedescriptor(NULL, &ex_struct);
	i--;
	while (i >= 0)
		waitpid(ex_struct.id[i--], &(*envp)->exit_status, 0);
	if(WIFEXITED((*envp)->exit_status))
		(*envp)->exit_status = WEXITSTATUS((*envp)->exit_status);
	else if(WIFSIGNALED((*envp)->exit_status))
		(*envp)->exit_status = 128 + WTERMSIG((*envp)->exit_status);
	free(ex_struct.id);
	ex_struct.id = NULL;
	free_fds(ex_struct.fd);
	return (SUCCESS);
}
