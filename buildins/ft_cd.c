/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/28 22:34:44 by ecaliska         ###   ########.fr       */
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
static int	dot_dot(char *current, char **old, char **pwd)
{
	char	*go_back;
	char	*new_pwd;

	*old = ft_strdup(current);
	new_pwd = malloc(FILENAME_MAX);
	go_back = remove_after_schraegstrich(current);
	chdir(go_back);
	getcwd(new_pwd, FILENAME_MAX);
	*pwd = new_pwd;
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
	TODO CD				returns you to your login directory
	TODO CD ~				also returns you to your login directory
	?CD -				takes you back to the oldpwd
	?CD /				takes you to the entire system's root directory
	?CD /root			takes you to the home directory of the root, or superuser, account created at installation 
	?CD /home			takes you to the home directory, where user login directories are usually stored
	?CD ..				moves you up one directory
	!CD ~otheruser		takes you to otheruser's login directory, if otheruser has granted you permission
	?CD /dir1/subdirfoo	regardless of which directory you are in, this absolute path would take you straight to subdirfoo, a subdirectory of dir1
	?CD ../../dir3/X11	this relative path would take you up two directories to root, then to dir3, then to the X11 directory.
*/

static int	get_mallocs(char **new)
{
	*new = malloc(FILENAME_MAX);
	if (!new)
		return (ERROR);
	if (getcwd(*new, FILENAME_MAX) == NULL)
	{
		perror("ft_cd getcwd");
		free (new);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	go_back(t_env **old, t_env **current)
{
	char	*now;

	if (!(*old))
	{
		write(2, "ShellMate: cd: OLDPWD not set\n", 31);
		return (ERROR);
	}
	now = malloc(FILENAME_MAX);
	getcwd(now, FILENAME_MAX);
	chdir((*old)->values);
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
	char	*new;
	t_env	*home;
	t_env	*current;

	parse = *node;
	if (array_size(parse->command) > 2)
		return (write(2, "ShellMate: cd: too many arguments\n", 35));
	initialize_env_values(&home, &old, &current, lst);
	if (array_size(parse->command) == 1)
		return (only_cd(home, &current, &old));
	if (get_mallocs(&new) == ERROR)
		return (ERROR);
	if (ft_strcmp(parse->command[1], "..") == 0)
		return (dot_dot(new, &old->values, &current->values));
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
