/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/04 14:50:14 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*remove_after_schraegstrich(char *s)
{
	int	i;

	i = ft_strlen(s);
	while (--i)
	{
		if (s[i] == '/')
		{
			s[i] = 0;
			break ;
		}
	}
	return (s);
}

//set current directory to the value of OLDPWD
static int	dot_dot(t_env **old, t_env **current)
{
	//char	*new_pwd;
	// char	*tmp;

	//tmp = remove_after_schraegstrich((*current)->values);
	free((*old)->values);
	(*old)->values = ft_strdup((*current)->values);
	(*current)->values = remove_after_schraegstrich((*current)->values);
	if (chdir((*current)->values) == -1)
	{
		perror("CD..: CHDIR");
		return (ERROR);
	}
	//new_pwd = malloc(FILENAME_MAX);
	free((*current)->values);
	(*current)->values = malloc(FILENAME_MAX);
	if (getcwd((*current)->values, FILENAME_MAX) == NULL)
	{
		perror("CD..: GETCWD");
		return (ERROR);
	}
	//(*current)->values=ft_strdup(new_pwd);
	return (SUCCESS);
}

//TODO set OLDPWD to current pwd
static int	dot(t_env **old)
{
	if (!(*old))
		return (SUCCESS);
	free((*old)->values);
	(*old)->values = malloc(FILENAME_MAX);
	getcwd((*old)->values, FILENAME_MAX);
	return (SUCCESS);
}

static int	only_cd(t_env *home, t_env **current, t_env **old)
{
	if (!home)
	{
		write(2, "ShellMate: cd: HOME not set\n", 29);
		return (ERROR);
	}
	free((*old)->values);
	(*old)->values = ft_strdup((*current)->values);
	free((*current)->values);
	chdir(home->values);
	(*current)->values = malloc(FILENAME_MAX);
	getcwd((*current)->values, FILENAME_MAX);
	return (SUCCESS);
}

/*
	TODO	LOOK FOR WRONG INPUT SIZE
	TODO	IF NO OLDPWD ErrMes:(bash: cd: OLDPWD not set) WITH 'CD -' 
*/

/*
	?CD					returns you to your login directory
	?CD ~				also returns you to your login directory
	?CD -				takes you back to the oldpwd
	?CD /				takes you to the entire system's root directory
	?CD /root			takes you to the home directory of the root, or superuser, account created at installation 
	?CD /home			takes you to the home directory, where user login directories are usually stored
	?CD ..				moves you up one directory
	!CD ~otheruser		takes you to otheruser's login directory, if otheruser has granted you permission
	?CD /dir1/subdirfoo	regardless of which directory you are in, this absolute path would take you straight to subdirfoo, a subdirectory of dir1
	?CD ../../dir3/X11	this relative path would take you up two directories to root, then to dir3, then to the X11 directory.
*/

static int	go_back(t_env **old, t_env **current)
{
	char	*now;

	if (!(*old))
	{
		write(2, "ShellMate: cd: OLDPWD not set\n", 31); // this is shit
		return (ERROR);
	}
	now = malloc(FILENAME_MAX);
	if (getcwd(now, FILENAME_MAX) == NULL)
	{
		perror("CD -: GETCWD");
		return (ERROR);
	}
	if (chdir((*old)->values) == -1)
	{
		perror("CD -: CHDIR");
		return (ERROR);
	}
	free((*old)->values);
	if (!(*current))
		(*old)->values = ft_strdup(now);
	else
	{
		(*old)->values = ft_strdup((*current)->values);
		free((*current)->values);
		(*current)->values = malloc(FILENAME_MAX);
		getcwd((*current)->values, FILENAME_MAX);
	}
	return (SUCCESS);
}

static void	initialize_env_values(t_env **h, t_env **o, t_env **c, t_env **lst)
{
	*h = get_from_env(lst, "HOME");
	*o = get_from_env(lst, "OLDPWD");
	*c = get_from_env(lst, "PWD");
}

//ft_putstr_fd("IN FT_CD\n", 2);
int	ft_cd(t_env **lst, t_parse **node)
{
	t_parse	*parse;
	t_env	*old;
	t_env	*home;
	t_env	*current;

	parse = *node;
	if (array_size(parse->command) > 2)
		return (write(2, "ShellMate: cd: too many arguments\n", 35));
	initialize_env_values(&home, &old, &current, lst);
	if (array_size(parse->command) == 1 || ft_strcmp(parse->command[1], "~") == 0)
		return (only_cd(home, &current, &old));
	if (ft_strcmp(parse->command[1], "..") == 0)
		return (dot_dot(&old, &current));
	else if (ft_strcmp(parse->command[1], ".") == 0)
		return (dot(&old));
	else if (ft_strcmp(parse->command[1], "-") == 0)
		return (go_back(&old, &current));
	else
	{
		chdir(parse->command[1]);
		free(old->values);
		old->values = ft_strdup(current->values);
		free(current->values);
		current->values = malloc(FILENAME_MAX);
		getcwd(current->values, FILENAME_MAX);
		return (SUCCESS);
	}
	write(2, "ShellMate: cd: ", 16);
	write(2, parse->command[1], ft_strlen(parse->command[1]));
	write(2, ": No such file or directory", 28);
	return (SUCCESS);
}
