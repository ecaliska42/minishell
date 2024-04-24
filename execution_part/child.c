/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:30:48 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/24 20:12:22 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	check_dot_slash(char *command)
{
	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
	{
		if (opendir(command) != NULL)
		{
			write(2, command, ft_strlen(command));
			write(2, ": is a directory\n", 18);
			exit(126);
		}
		if (access(command, F_OK) == -1)
		{
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n", 28);
			exit(127);
		}
		if (access(command, X_OK) == -1)
		{
			write(2, command, ft_strlen(command));
			write(2, ": Permission denied\n", 21);
			exit(126);
		}
	}
}

static void	dup_and_close(t_mini *ms, int i, t_parse *comm)
{
	if (ms->exe.pipecount != 0)
	{
		dup_filedescriptor(comm, &ms->exe, i);
		close_filedescriptor(comm, &ms->exe);
	}
	else
		dup_for_no_pipes(comm);
}

void	print_command_not_found(char **command, t_mini **mini)
{
	while (*command && **command == '\0')
		command++;
	write(2, *command, ft_strlen(*command));
	write(2, ": command not found\n", 21);
	(*mini)->exit_status = 127;
}

int	child(t_parse *comm, int i, t_mini **mini)
{
	t_mini	*ms;
	char	**envp;

	ms = *mini;
	if (comm->execute == IGNORE)
		exit(1);
	check_dot_slash(comm->command[0]);
	envp = change_envp(&ms->env);
	if (!envp)
		return (ERROR);
	dup_and_close(ms, i, comm);
	if (is_buildin(comm->command) == true)
	{
		execute_buildin(&comm, &ms->env, ms->exe.pipecount, &ms);
		close_filedescriptor(comm, &ms->exe);
		exit (SUCCESS);
	}
	close_filedescriptor(comm, &ms->exe);
	execve(comm->check, comm->command, envp);
	if (comm->empty == false || comm->command[0][0] != '\0')
		print_command_not_found(comm->command, mini);
	check_malloc_exit(NULL, ms);
	return(1);
}
//IDK ABOUT CLOSE FILE DESCRIPTOR IN IF IS BUILDIN STATEMENT