/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/16 12:54:03 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

int		parrent_buildin(char *s, t_env **envp)
{
	//printf("in function parrent_buildin\n");
	if (ft_strncmp("cd", s, 3) == 0)
		ft_cd(envp, s);
	if (ft_strncmp("exit", s, 5) == 0)
		ft_exit();
	return (0);
}

bool	is_parrent_buildin(char **s)
{
	//printf("in function is_parrent buildin\n");
	if (!s)
		return false;
	char *str;

	str = s[0];
	if (ft_strncmp("cd", str, 3) == 0)
		return true;
	if (ft_strncmp("exit", str, 5) == 0)
		return true;
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
	
	return false;
}

int		execute_buildin(char **s, t_env **envp)
{
	//printf("command [0]=%s\n", s[0]);
	//printf("command [1]=%s\n", s[1]);
	//printf("command [2]=%s\n", s[2]);
	if (ft_strncmp("echo ", s[0], 4) == 0)
		ft_echo(s[1]);
	if (ft_strncmp("pwd", s[0], 4) == 0)
		ft_pwd();
	if (ft_strncmp("env", s[0], 4) == 0)
		ft_env(envp);
	
	return 0;
}