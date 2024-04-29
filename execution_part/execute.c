/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 19:30:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/28 13:21:28 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	fork_childs(t_parse *parse, int *i, t_mini **mini)
{
	t_parse *tmp;

	tmp = parse;
	*i = 0;
	while (parse != NULL)
	{
		(*mini)->exe.id[*i] = fork();
		if ((*mini)->exe.id[*i] == -1)
			free_mini_and_exit(mini);
		if ((*mini)->exe.id[*i] == 0)
		{
			signal_handler(2, *mini);
			child(parse, *i, mini, tmp);
		}
		(*i)++;
		parse = parse->next;
	}
	(*i)--;
}

static bool	check_solo_buildin(t_parse *parse, t_mini **mini)
{
	if (is_buildin(parse->command) == true && (*mini)->exe.pipecount == 0
		&& parse->execute == EXECUTE)
	{
		lonely_buildin(parse, &(*mini)->env, mini);
		free_and_null((void **)&(*mini)->exe.id);
		free_fds((*mini)->exe.fd);
		return (true);
	}
	return (false);
}

static void	wait_for_children(t_mini **mini, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		waitpid((*mini)->exe.id[j], &(*mini)->exit_status, 0);
		j++ ;
	}
}

int	close_pipes(t_exe *exe)
{
	int	i;

	i = 0;
	while (exe->fd[i])
	{
		close(exe->fd[i][0]);
		close(exe->fd[i][1]);
		i++;
	}
	return (SUCCESS);
}

int	close_parse(t_parse *parse)
{
	while (parse)
	{
		if (parse->infd > 0)
			close(parse->infd);
		if (parse->outfd > 0)
			close(parse->outfd);
		parse = parse->next;
	}
	return (SUCCESS);
}

int	execute(t_mini **mini)
{
	t_parse	*parse;
	int		i;

	parse = (*mini)->parse;
	if (malloc_ex_struct(&(*mini)->exe) == ERROR)
		return (ERROR);
	if (check_solo_buildin(parse, mini) == true)
	{
		free_exe(&(*mini)->exe);
		return (SUCCESS);
	}
	if (create_pipes(&(*mini)->exe) == ERROR)
		return (ERROR);
	fork_childs(parse, &i, mini);
	close_filedescriptor(parse, &(*mini)->exe);
	// close_pipes(&(*mini)->exe);
	// close_parse(parse);
	wait_for_children(mini, i);
	if (WIFEXITED((*mini)->exit_status))
		(*mini)->exit_status = WEXITSTATUS((*mini)->exit_status);
	else if (WIFSIGNALED((*mini)->exit_status))
		(*mini)->exit_status = 128 + WTERMSIG((*mini)->exit_status);
	free_and_null((void **)&(*mini)->exe.id);
	free_exe(&(*mini)->exe);
	return (SUCCESS);
}
