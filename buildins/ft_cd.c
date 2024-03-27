/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/27 23:43:38 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// static int full_path(char *s)
// {
// 	(void)s;
// 	return 0;
// }

static char *remove_after_schraegstrich(char *s)
{
	int i = ft_strlen(s);
	while (--i)
	{
		if (s[i] == '/')
		{
			s[i] = 0;
			break;
		}
	}
	return (s);
}

// static int dot(void)
// {
// 	return 0;
// }

// static int dot_dot(char *current, char **old)//set current directory to the value of OLDPWD
// {
// 	char *new_old = malloc(FILENAME_MAX);
// 	if (!new_old)
// 		return (ERROR);
// 	char *go_back;//get the directory before the last schraegstrich
// 	go_back = remove_after_schraegstrich(current);
// 	printf("go_back=%s\n", go_back);
// 	chdir(go_back);
// 	getcwd(new_old, FILENAME_MAX);
// 	*old = ft_strdup(new_old);
// 	return (SUCCESS);
// 	*old = current;
// }

static int do_do(char *current, char **old, char **pwd)//set current directory to the value of OLDPWD
{
	char	*go_back;//get the directory before the last schraegstrich
	char	*new_pwd;

	*old = ft_strdup(current);
	new_pwd = malloc(FILENAME_MAX);
	go_back = remove_after_schraegstrich(current);
	printf("go_back=%s\n", go_back);
	chdir(go_back);
	getcwd(new_pwd, FILENAME_MAX);
	*pwd = new_pwd;
	return (SUCCESS);
}


t_env	*get_from_env(t_env **lst, char *s)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// int	ft_cd(t_env **lst, char *s, t_parse **node)
// {
// 	//ft_putendl_fd("IN CD", 2);
// 	t_env	*tmp;	//get the oldpwd value
// 	char	*current_dir;//get the current directory with getcwd
// 	int		i;
// 	char	*get_arg;//get the argument after cd like cd .. or cd . or cd ~ that means get_arg is . or .. or ~
// 	// printf("HERE\n");
// 	i = 0;
// 	tmp = *lst;
// 	current_dir = malloc(FILENAME_MAX);
// 	if(getcwd(current_dir, FILENAME_MAX) == NULL)
// 	{
// 		perror("");
// 		free(current_dir);
// 		return 1;
// 	}
// 	tmp = get_from_env(lst, "OLDPWD");
// 	if (!tmp)
// 		return 1;
// 	// printf("OLDPWD=%s\n", tmp->values[0]);
// 	get_arg = get_after(s, ' ');
// 	//get_arg = ft_strchr(s, ' ');
// 	printf("s=%s\n", s);
// 	printf("get_arg=%s\n", get_arg);
// 	if (ft_strncmp(get_arg, ".", 1) == 0)
// 	{
// 		if (ft_strncmp(get_arg, "..", 2) == 0)
// 			dot_dot(current_dir, &tmp->values);// CURRENT_DIR || OLDPWD VALUE
// 		else
// 			dot();
// 	}
// 	else
// 	{
		
// 	}

// 	return 0;
// }

/*
	TODO	LOOK FOR WRONG INPUT SIZE
	TODO	IF NO OLDPWD ErrMes:(bash: cd: OLDPWD not set) WITH 'CD -' 
*/

/*
	CD					returns you to your login directory
	CD ~				also returns you to your login directory
	CD /				takes you to the entire system's root directory
	CD /root			takes you to the home directory of the root, or superuser, account created at installation 
	CD /home			takes you to the home directory, where user login directories are usually stored
	?CD ..				moves you up one directory
	CD ~otheruser		takes you to otheruser's login directory, if otheruser has granted you permission
	CD /dir1/subdirfoo	regardless of which directory you are in, this absolute path would take you straight to subdirfoo, a subdirectory of dir1
	CD ../../dir3/X11	this relative path would take you up two directories to root, then to dir3, then to the X11 directory.
*/

int	get_mallocs(char **new, char ***actions, char *arguments)
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
	*actions = ft_split(arguments, '/');
	if (!actions)
	{
		perror("ft_cd actions ft_split");
		free(new);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	go_back(void)
{
	return (SUCCESS);
}

int	ft_cd(t_env **lst, t_parse **node)
{
	ft_putstr_fd("IN FT_CD\n", 2);
	t_parse	*parse;
	t_env	*old;
	char	*new;
	t_env	*current;
	t_env	*env;
	char	**actions;
	
	parse = *node;
	env = *lst;
	if (array_size(parse->command) > 2)
		return (write(2, "ShellMate: cd: too many arguments\n", 35));
	if (array_size(parse->command) == 1)
		return (ERROR);//!change to home directory
	if (get_mallocs(&new, &actions, parse->command[1]) == ERROR)
		return (ERROR);
	// new = get_env_value("PWD", env);
	old = get_from_env(&env, "OLDPWD");//?IS THE OLDPWD IS NULL IF NO OLDPWD FOR CD- && is pointing to the OLDPWD node
	current = get_from_env(&env, "PWD");//? SHOULD BE POINTING TO THE PWD NODE
	if (ft_strcmp(parse->command[1], "..") == 0)
		return (do_do(new, &old->values, &current->values));
	else if (ft_strcmp(parse->command[1], ".") == 0)
		return (SUCCESS);
	else if (ft_strcmp(parse->command[1], "-") == 0)
		return (go_back()); //! change directory to OLDPWD && if no OLDPWD write out an error message
	else//TODO IS ABSOLOUTE PATH
	{
		chdir(parse->command[1]);
		
		return (SUCCESS);
	}
	write(2, "ShellMate: cd: ", 16);
	write(2, parse->command[1], ft_strlen(parse->command[1]));
	write(2, ": No such file or directory", 28);
	return (SUCCESS);
}
