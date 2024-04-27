/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:30:48 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/27 13:17:07 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	check_dot_slash(char *command, t_mini **mini)
{
	if (command && (command[0] == '/'
		|| (command[0] == '.' && command[1] == '/')))
	{
		if (opendir(command) != NULL)
		{
			write(2, command, ft_strlen(command));
			write(2, ": is a directory\n", 18);
			(*mini)->exit_status = 126;
			free_mini_and_exit(mini);
		}
		if (access(command, F_OK) == -1)
		{
			write(2, command, ft_strlen(command));
			write(2, ": No such file or directory\n", 28);
			(*mini)->exit_status = 127;
			free_mini_and_exit(mini);
		}
		if (access(command, X_OK) == -1)
		{
			write(2, command, ft_strlen(command));
			write(2, ": Permission denied\n", 21);
			(*mini)->exit_status = 126;
			free_mini_and_exit(mini);
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

static void	is_really_buildin(t_parse *comm, t_mini *ms, char **envp)
{
	execute_buildin(&comm, &ms->env, ms->exe.pipecount, &ms);
	close_filedescriptor(comm, &ms->exe);
	free_double(envp);
	ms->exit_status = 0;
	free_mini_and_exit(&ms);
}

void	check_exit(t_mini **mini, t_parse *comm)
{
	if (comm && comm->execute == IGNORE)
	{
		(*mini)->exit_status = 1;
		free_mini_and_exit(mini);
	}
	if (!comm->command && !comm->outfd)
		free_mini_and_exit(mini);
}

int	child(t_parse *comm, int i, t_mini **mini)
{
	t_mini	*ms;
	char	**envp;

	ms = *mini;
	check_exit(mini, comm);
	if (comm->command && comm->command[0])
		check_dot_slash(comm->command[0], mini);
	envp = change_envp(&ms->env, *mini);
	if (!envp)
		return (ERROR);
	dup_and_close(ms, i, comm);
	if (is_buildin(comm->command) == true)
		is_really_buildin(comm, ms, envp);
	close_filedescriptor(comm, &ms->exe);
	if (g_sig || !comm->command || !comm->command[0])
	{
		free_double(envp);
		free_mini_and_exit(&ms);
	}
	execve(comm->check, comm->command, envp);
	if (comm->empty == false || comm->command[0][0] != '\0')
		print_command_not_found(comm->command, mini);
	free_double(envp);
	check_malloc_exit(NULL, ms);
	return (1);
}
