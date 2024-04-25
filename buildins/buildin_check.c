/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/25 15:23:46 by mesenyur         ###   ########.fr       */
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

int	lonely_buildin(t_parse *parse, t_env **envp, t_mini **mini)
{
	if (open_lonely_files(&parse) == ERROR)
		return (ERROR);
	execute_buildin(&parse, envp, 0, mini);
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
		ft_pwd(mini);
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
