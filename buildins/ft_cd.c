/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 15:03:13 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	initialize_env_values(t_env **h, t_env **o, t_env **c, t_env **lst)
{
	*h = get_from_env(lst, "HOME");
	*o = get_from_env(lst, "OLDPWD");
	*c = get_from_env(lst, "PWD");
}

//ft_putstr_fd("IN FT_CD\n", 2);
int	ft_cd(t_env **lst, t_parse **node, t_mini **mini)
{
	t_parse	*parse;
	t_env	*old;
	t_env	*home;
	t_env	*current;

	parse = *node;
	if (array_size(parse->command) > 2)
	{
		(*mini)->exit_status = 1;
		return (write(2, "ShellMate: cd: too many arguments\n", 35));
	}
	initialize_env_values(&home, &old, &current, lst);
	if (array_size(parse->command) == 1
		|| ft_strcmp(parse->command[1], "~") == 0)
	{
		(*mini)->exit_status = 0;
		return (only_cd(home, &current, &old));
	}
	if (ft_strcmp(parse->command[1], "..") == 0)
	{
		(*mini)->exit_status = 0;
		return (dot_dot(&old, &current));
	}
	else if (ft_strcmp(parse->command[1], ".") == 0)
	{
		(*mini)->exit_status = 0;
		return (dot(&old));
	}
	else if (ft_strcmp(parse->command[1], "-") == 0)
		return (go_back(&old, &current, mini));
	else
	{
		if (chdir(parse->command[1]) != -1)
		{
			if (old && old->values)
			{
				free(old->values);
				old->values = ft_strdup(current->values);
			}
			if (current && current->values)
			{
				free(current->values);
				current->values = malloc(FILENAME_MAX);
				getcwd(current->values, FILENAME_MAX);
			}
			(*mini)->exit_status = 0;
			return (SUCCESS);
		}
	}
	write(2, "ShellMate: cd: ", 16);
	write(2, parse->command[1], ft_strlen(parse->command[1]));
	write(2, ": No such file or directory\n", 29);
	(*mini)->exit_status = 1;
	return (SUCCESS);
}
