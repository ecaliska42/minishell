/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:55:29 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 16:05:57 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*remove_after_schraegstrich(char *s)
{
	int	i;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (--i >= 0)
	{
		if (s[i] == '/')
		{
			s[i] = 0;
			break ;
		}
	}
	if (i <= 0)
	{
		free(s);
		s = ft_strdup("/");
	}
	return (s);
}

//set current directory to the value of OLDPWD
int	dot_dot(t_env **old, t_env **current)
{
	char	*current_dir;
	char	*change_dir;

	current_dir = malloc(FILENAME_MAX);
	getcwd(current_dir, FILENAME_MAX);
	change_dir = remove_after_schraegstrich(ft_strdup(current_dir));
	if ((*old) && (*old)->values)
	{
		free((*old)->values);
		(*old)->values = ft_strdup(current_dir);
	}
	if ((*current) && (*current)->values)
	{
		if (chdir(change_dir) == -1)
			return_write("CD..: CHDIR", ERROR);
		free((*current)->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (getcwd((*current)->values, FILENAME_MAX) == NULL)
			return_write("CD..: GETCWD", ERROR);
		return (SUCCESS);
	}
	else
		if (chdir(change_dir) == -1)
			return_write("CD..: CHDIR", ERROR);
	return (SUCCESS);
}

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
		getcwd((*current)->values, FILENAME_MAX);
	}
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
	{
		perror("CD -: GETCWD");
		free(now);
		return (ERROR);
	}
	if (chdir((*old)->values) == -1)
	{
		perror("CD -: CHDIR");
		free(now);
		return (ERROR);
	}
	free((*old)->values);
	if (!(*current))
	{
		(*old)->values = ft_strdup(now);
		if (!(*old)->values)
		{
			free(now);
			return (ERROR);
		}
	}
	else
	{
		(*old)->values = ft_strdup((*current)->values);
		if (!(*old)->values)
		{
			free(now);
			return (ERROR);
		}
		free((*current)->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (!(*current)->values)
		{
			free(now);
			return (ERROR);
		}
		if (!getcwd((*current)->values, FILENAME_MAX))
		{
			perror("CD -: GETCWD");
			free(now);
			return (ERROR);
		}
		printf("%s\n", (*current)->values);
	}
	(*mini)->exit_status = 0;
	free(now);
	return (SUCCESS);
}
