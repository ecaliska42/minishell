/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/19 13:47:17 by ecaliska         ###   ########.fr       */
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

	s = command[0];
	if (ft_strncmp("echo ", s, 4) == 0)
		return true;
	if (ft_strncmp("pwd", s, 4) == 0)
		return true;
	if (ft_strncmp("env", s, 4) == 0)
		return true;
	if (ft_strncmp("cd", s, 3) == 0)
		return true;
	if (ft_strncmp("exit", s, 5) == 0)
		return true;
	return false;
}

int		execute_buildin(char **command, t_env **envp, t_token **head)
{
	char	*s;

	s = command[0];
	if (!s)
		return 0;
	if (ft_strncmp("echo ", s, 4) == 0)
		ft_echo(head);
	if (ft_strncmp("pwd", s, 4) == 0)
		ft_pwd();
	if (ft_strncmp("env", s, 4) == 0)
		ft_env(envp);
	if (ft_strncmp("cd", s, 3) == 0)
		ft_cd(envp, s);
	if (ft_strncmp("exit", s, 4) == 0)
		ft_exit();
	return (0);
}