/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/20 20:25:06 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libraries/parsing.h"

int		parrent_buildin(char *s, t_env **envp)
{
	//printf("in function parrent_buildin\n");
	(void)envp;
	(void)s;
	return 0;
}

bool	is_parrent_buildin(char **s)
{
	//printf("in function is_parrent buildin\n");
	if (!s)
		return false;
	char *str;

	str = s[0];
	return false;
}

bool	is_buildin(char **command)
{
	char	*s;

	if (!command)
		return false;
	s = command[0];
	if (ft_strcmp("echo", s) == 0)
		return true;
	else if (ft_strcmp("pwd", s) == 0)
		return true;
	else if (ft_strcmp("env", s) == 0)
		return true;
	else if (ft_strcmp("cd", s) == 0)
		return true;
	else if (ft_strcmp("exit", s) == 0)
		return true;
	return false;
}

int		execute_buildin(char **command, t_env **envp, t_token **head)
{
	char	*s;

	s = command[0];
	if (!s)
		return 0;
	if (ft_strcmp("echo", s) == 0)
		ft_echo(head);
	else if (ft_strcmp("pwd", s) == 0)
		ft_pwd();
	else if (ft_strcmp("env", s) == 0)
		ft_env(envp);
	else if (ft_strcmp("cd", s) == 0)
		ft_cd(envp, s);
	else if (ft_strcmp("exit", s) == 0)
		ft_exit();
	return (0);
}