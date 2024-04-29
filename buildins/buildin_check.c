/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:40:24 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	open_lonely_files(t_parse **parse)
{
	if ((*parse)->outfd > 0)
	{
		dup2((*parse)->outfd, 1);
		close((*parse)->outfd);
	}
	if ((*parse)->infd > 0)
	{
		dup2((*parse)->infd, 0);
		close((*parse)->infd);
	}
	return (SUCCESS);
}

int	set_struct(t_lonely_buildin *lb, char *command)
{
	if (ft_strcmp("exit", command) == 0)
		lb->flag = 0;
	else
		lb->flag = 1;
	if (lb->flag == 1)
	{
		lb->orig_stdout = dup(1);
		if (lb->orig_stdout == -1)
			return (ERROR);
		lb->orig_stdin = dup(0);
		if (lb->orig_stdin == -1)
		{
			close(lb->orig_stdout);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	lonely_buildin(t_parse *parse, t_env **envp, t_mini **mini)
{
	t_lonely_buildin	lb;

	if (set_struct(&lb, parse->command[0]) == ERROR)
		return (ERROR);
	if (open_lonely_files(&parse) == ERROR)
		return (ERROR);
	execute_buildin(&parse, envp, 0, mini);
	if (lb.flag == 1)
	{
		if (dup2(lb.orig_stdin, STDIN_FILENO) == -1)
			perror("dup2 error (execute.c) : ");
		if (close (lb.orig_stdin) == -1)
			perror("close error (execute.c) : ");
		if (dup2(lb.orig_stdout, STDOUT_FILENO) == -1)
			perror("dup2 error (execute.c) : ");
		if (close (lb.orig_stdout) == -1)
			perror("close error (execute.c) : ");
	}
	return (SUCCESS);
}

bool	is_buildin(char **command)
{
	char	*s;

	if (!command)
		return (false);
	s = command[0];
	if (ft_strcmp("echo", s) == 0)
		return (true);
	else if (ft_strcmp("pwd", s) == 0)
		return (true);
	else if (ft_strcmp("env", s) == 0)
		return (true);
	else if (ft_strcmp("cd", s) == 0)
		return (true);
	else if (ft_strcmp("exit", s) == 0)
		return (true);
	else if (ft_strcmp("unset", s) == 0)
		return (true);
	else if (ft_strcmp("export", s) == 0)
		return (true);
	return (false);
}

int	execute_buildin(t_parse **parse, t_env **env, int pc, t_mini **mini)
{
	char	*s;

	s = (*parse)->command[0];
	if (!s)
		return (0);
	if (ft_strcmp("echo", s) == 0)
		ft_echo(parse, mini);
	else if (ft_strcmp("pwd", s) == 0)
		return (ft_pwd(mini));
	else if (ft_strcmp("env", s) == 0)
		ft_env(env, mini, parse);
	else if (ft_strcmp("cd", s) == 0 && pc == 0)
		ft_cd(env, parse, mini);
	else if (ft_strcmp("exit", s) == 0)
		ft_exit(parse, mini);
	else if (ft_strcmp("unset", s) == 0 && pc == 0)
		ft_unset(parse, env, mini);
	else if (ft_strcmp("export", s) == 0)
		ft_export(env, parse, mini);
	return (0);
}
