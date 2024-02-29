/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/28 18:41:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_buildin(char **command, t_env **envp)
{
	char	*s;

	s = command[0];
	if (ft_strncmp("echo ", s, 6) == 0)
		ft_echo(ft_strchr(s, ' '));
	if (ft_strncmp("pwd", s, 4) == 0)
		ft_pwd();
	if (ft_strncmp("env", s, 4) == 0)
		ft_env(envp);
	if (ft_strncmp("exit", s, 5) == 0)
		ft_exit();
}

int		execute_buildin(char *s, t_env **envp)
{
	if (ft_strncmp("echo ", s, 6) == 0)
		ft_echo(ft_strchr(s, ' '));
	if (ft_strncmp("pwd", s, 4) == 0)
		ft_pwd();
	if (ft_strncmp("env", s, 4) == 0)
		ft_env(envp);
	if (ft_strncmp("exit", s, 5) == 0)
		ft_exit();
	return 0;
}