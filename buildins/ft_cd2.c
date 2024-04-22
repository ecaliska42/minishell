/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:55:29 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 19:39:11 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	dot(t_env **old)
{
	if (!(*old))
		return (SUCCESS);
	free((*old)->values);
	(*old)->values = malloc(FILENAME_MAX);
	getcwd((*old)->values, FILENAME_MAX);
	return (SUCCESS);
}

int	only_cd(t_env *home, t_env **current, t_env **old)
{
	if (!home)
		return_write("ShellMate: cd: HOME not set", ERROR);
	if ((*old) && (*old)->values)
	{
		free((*old)->values);
		(*old)->values = ft_strdup((*current)->values);
	}
	if ((*current) && (*current)->values)
	{
		free((*current)->values);
		chdir(home->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (!(*current)->values)
			return (ERROR);
		if (!getcwd((*current)->values, FILENAME_MAX))
			return (ERROR);
	}
	return (SUCCESS);
}

int	ch_dir_else(t_env **old, t_env **current, char *now)
{
	(*old)->values = ft_strdup((*current)->values);
	if (!(*old)->values)
		return (free(now), ERROR);
	free((*current)->values);
	(*current)->values = malloc(FILENAME_MAX);
	if (!(*current)->values)
		return (free(now), ERROR);
	if (!getcwd((*current)->values, FILENAME_MAX))
	{
		perror("CD -: GETCWD");
		return (free(now), ERROR);
	}
	printf("%s\n", (*current)->values);
	return (SUCCESS);
}

int	go_back(t_env **old, t_env **current, t_mini **mini)
{
	char	*now;

	if (!(*old))
	{
		(*mini)->exit_status = 1;
		return_write("ShellMate: cd: OLDPWD not set", ERROR);
	}
	now = malloc(FILENAME_MAX);
	if (!now)
		return (ERROR);
	if (getcwd(now, FILENAME_MAX) == NULL)
		return (free(now), ERROR);
	if (chdir((*old)->values) == -1)
		return (free(now), ERROR);
	free((*old)->values);
	if (!(*current))
	{
		(*old)->values = ft_strdup(now);
		if (!(*old)->values)
			return (free(now), ERROR);
	}
	else
		ch_dir_else(old, current, now);
	(*mini)->exit_status = 0;
	return (free(now), SUCCESS);
}
