/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:55:51 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	initialize_env_values(t_env **h, t_env **o, t_env **c, t_env **lst)
{
	*h = get_from_env(lst, "HOME");
	*o = get_from_env(lst, "OLDPWD");
	*c = get_from_env(lst, "PWD");
}

int	check_dots_and_only(char **command, t_mini **mini, t_cd *cd_str)
{
	if (array_size(command) == 1 || ft_strcmp(command[1], "~") == 0)
	{
		(*mini)->exit_status = 0;
		if (only_cd(cd_str->home, &cd_str->current, &cd_str->old) == ERROR)
			(*mini)->exit_status = 1;
		return (SUCCESS);
	}
	if (ft_strcmp(cd_str->parse->command[1], "..") == 0)
	{
		(*mini)->exit_status = 0;
		return (dot_dot(&cd_str->old, &cd_str->current, *mini));
	}
	else if (ft_strcmp(cd_str->parse->command[1], ".") == 0)
	{
		(*mini)->exit_status = 0;
		return (dot(&cd_str->old));
	}
	else if (ft_strcmp(cd_str->parse->command[1], "-") == 0)
		return (go_back(&cd_str->old, &cd_str->current, mini));
	return (5);
}

int	change_dir_helper(t_mini **mini, t_cd *cd_str)
{
	if (cd_str->current && cd_str->current->values)
	{
		free_and_null((void **)&cd_str->current->values);
		cd_str->current->values = malloc(FILENAME_MAX);
		if (!cd_str->current->values)
			free_mini_and_exit(mini);
		if (!getcwd(cd_str->current->values, FILENAME_MAX))
			return (10);
	}
	(*mini)->exit_status = 0;
	return (SUCCESS);
}

int	change_dir(t_cd *cd_str, t_mini **mini)
{
	char	*pwd;

	pwd = malloc(FILENAME_MAX);
	if (!pwd)
		return (10);
	if (!getcwd(pwd, FILENAME_MAX))
		return (free_and_null((void **)&pwd), 10);
	if (chdir(cd_str->parse->command[1]) != -1)
	{
		if (cd_str->old && cd_str->old->values)
		{
			free_and_null((void **)&cd_str->old->values);
			cd_str->old->values = ft_strdup(pwd);
			if (!cd_str->old->values)
				return (free_and_null((void **)&pwd), 10);
		}
		free_and_null((void **)&pwd);
		if (change_dir_helper(mini, cd_str) == 10)
			return (10);
		return (SUCCESS);
	}
	free_and_null((void **)&pwd);
	(*mini)->exit_status = 1;
	return (ERROR);
}

int	ft_cd(t_env **lst, t_parse **node, t_mini **mini)
{
	t_cd	cd_str;
	int		check;

	cd_str.parse = *node;
	check = 0;
	if (array_size(cd_str.parse->command) > 2)
	{
		(*mini)->exit_status = 1;
		return (return_write("ShellMate: cd: too many arguments", ERROR));
	}
	initialize_env_values(&cd_str.home, &cd_str.old, &cd_str.current, lst);
	if (check_dots_and_only(cd_str.parse->command, mini, &cd_str) != 5)
		return (SUCCESS);
	check = change_dir(&cd_str, mini);
	if (check != SUCCESS && check != 10)
	{
		write(2, "ShellMate: cd: ", 16);
		write(2, cd_str.parse->command[1], ft_strlen(cd_str.parse->command[1]));
		write(2, ": No such file or directory\n", 29);
		(*mini)->exit_status = 1;
	}
	return (SUCCESS);
}
