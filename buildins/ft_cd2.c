/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:55:29 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:50:46 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	dot(t_env **old)
{
	if (!(*old))
		return (SUCCESS);
	free_and_null((void **)&(*old)->values);
	(*old)->values = malloc(FILENAME_MAX);
	getcwd((*old)->values, FILENAME_MAX);
	return (SUCCESS);
}

int	only_cd_helper(t_env *home, t_env **current)
{
	if ((*current) && (*current)->values)
	{
		free_and_null((void **)&(*current)->values);
		chdir(home->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (!(*current)->values)
			return (ERROR);
		if (!getcwd((*current)->values, FILENAME_MAX))
			return (ERROR);
	}
	return (SUCCESS);
}

int	only_cd(t_env *home, t_env **current, t_env **old)
{
	char	*pwd;

	if (!home)
		return (return_write("ShellMate: cd: HOME not set", ERROR));
	pwd = malloc(FILENAME_MAX);
	if (!pwd)
		return (ERROR);
	if (!getcwd(pwd, FILENAME_MAX))
		return (free_and_null((void **)&pwd), ERROR);
	if ((*old) && (*old)->values)
	{
		free_and_null((void **)&(*old)->values);
		(*old)->values = ft_strdup(pwd);
		if (!(*old)->values)
			return (free_and_null((void **)&pwd), ERROR);
	}
	free_and_null((void **)&pwd);
	if (only_cd_helper(home, current) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	go_back_helper(t_env **old, t_mini **mini, char *now)
{
	if (chdir((*old)->values) == -1)
	{
		perror("CD -: CHDIR");
		(*mini)->exit_status = 1;
		return (free_and_null((void **)&now), ERROR);
	}
	return (SUCCESS);
}

int	go_back(t_env **old, t_env **current, t_mini **mini)
{
	char	*now;

	if (!(*old) || !(*old)->values)
	{
		(*mini)->exit_status = 1;
		return (return_write("cd: OLDPWD not set", ERROR));
	}
	now = malloc(FILENAME_MAX);
	if (!now)
		return (ERROR);
	if (getcwd(now, FILENAME_MAX) == NULL)
		return (free_and_null((void **)&now), ERROR);
	if (go_back_helper(old, mini, now) == ERROR)
		return (ERROR);
	free_and_null((void **)&(*old)->values);
	if (!(*current))
	{
		(*old)->values = ft_strdup(now);
		if (!(*old)->values)
			return (free_and_null((void **)&now), ERROR);
	}
	else
		ch_dir_else(old, current, now);
	(*mini)->exit_status = 0;
	return (free_and_null((void **)&now), SUCCESS);
}
