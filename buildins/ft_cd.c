/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/26 19:18:52 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <stdio.h>
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

static int dot_dot(char *current, char **old)//set current directory to the value of OLDPWD
{
	if (ft_strlen(current) == 1)//!WRONG
		return 0;
	char *new_old = malloc(FILENAME_MAX);
	char *go_back;//get the directory before the last schraegstrich
	go_back = remove_after_schraegstrich(current);
	printf("go_back=%s\n", go_back);
	chdir(go_back);
	new_old = getcwd(new_old, FILENAME_MAX);
	*old = ft_strdup(new_old);
	return 0;
}

t_env	*get_from_env(t_env **lst, char *s)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, s, ft_strlen(s)) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
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
	
*/

int	ft_cd(t_env **lst, t_parse **node)
{
	int	i;
	t_parse	*parse;
	char	*old;
	char	*new;
	t_env	*env;
	
	parse = *node;
	env = *lst;
	new = malloc(FILENAME_MAX);
	if (!new)
		return (ERROR);
	if (getcwd(new, FILENAME_MAX) == NULL)
	{
		perror("cd getcwd");
		free(new);
		return (ERROR);
	}
	// new = get_env_value("PWD", env);
	old = get_env_value("OLDPWD", env);
	i = 1;
	if (array_size(parse->command) > 2)
		return (write(2, "ShellMate: cd: too many arguments\n", 35));
	if (ft_strcmp(parse->command[i], "..") == 0)
		dot_dot(new, &old);
	return (SUCCESS);
}