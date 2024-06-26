/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:30:48 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/03 13:38:45 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	check_dot_slash(char *command, t_mini **mini)
{
	if (command && (command[0] == '/'
			|| (command[0] == '.' && command[1] == '/')))
	{
		check_dir(command, mini);
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

static void	dup_and_close(t_mini *ms, int i, t_parse *comm, char **envp)
{
	if (ms->exe.pipecount != 0)
	{
		if (dup_filedescriptor(comm, &ms->exe, i) == ERROR)
		{
			free_double(envp);
			close_filedescriptor(comm, &ms->exe);
			free_mini_and_exit(&ms);
		}
		close_filedescriptor(comm, &ms->exe);
		return ;
	}
	else if (dup_for_no_pipes(comm) == NULL)
	{
		free_double(envp);
		close_filedescriptor(comm, &ms->exe);
		free_mini_and_exit(&ms);
	}
}

void	is_really_buildin(t_parse *comm, t_mini *ms, char **envp, t_parse *head)
{
	execute_buildin(&comm, &ms->env, ms->exe.pipecount, &ms);
	close_filedescriptor(head, &ms->exe);
	free_double(envp);
	ms->exit_status = 0;
	free_mini_and_exit(&ms);
}

void	check_exit(t_mini **mini, t_parse *comm, t_parse *head)
{
	if (comm && comm->execute == IGNORE)
	{
		(*mini)->exit_status = 1;
		close_filedescriptor(head, &(*mini)->exe);
		free_mini_and_exit(mini);
	}
	if (!comm->command && !comm->outfd && g_sig != 0)
	{
		(*mini)->exit_status = 1;
		close_filedescriptor(head, &(*mini)->exe);
		free_mini_and_exit(mini);
	}
}

int	child(t_parse *comm, int i, t_mini **mini, t_parse *head)
{
	t_mini	*ms;
	char	**envp;

	ms = *mini;
	check_exit(mini, comm, head);
	if (comm->command && comm->command[0])
		check_dot_slash(comm->command[0], mini);
	envp = change_envp(&ms->env, *mini);
	if (!envp)
		return (ERROR);
	dup_and_close(ms, i, comm, envp);
	if (is_buildin(comm->command) == true)
		is_really_buildin(comm, ms, envp, head);
	close_filedescriptor(head, &ms->exe);
	if (g_sig || !comm->command || !comm->command[0])
	{
		free_double(envp);
		free_mini_and_exit(&ms);
	}
	if (comm->check)
		execve(comm->check, comm->command, envp);
	print_correct_error_message(comm, mini);
	free_double(envp);
	check_malloc_exit(NULL, ms);
	return (1);
}
