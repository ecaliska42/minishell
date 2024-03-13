/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/12 14:11:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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

static int dot(void)
{
	return 0;
}

static int dot_dot(char *current, char **old)
{
	if (ft_strlen(current) == 1)//!WRONG
		return 0;
	char *new_old = malloc(FILENAME_MAX);
	chdir(remove_after_schraegstrich(current));
	new_old = getcwd(new_old, FILENAME_MAX);
	*old = ft_strdup(new_old);
	return 0;
}

int	ft_cd(t_env **lst, char *s)
{
	t_env	*tmp;
	int		i;
	char	*current_dir;
	char	*get_arg;
	// printf("HERE\n");
	i = 0;
	tmp = *lst;
	current_dir = malloc(FILENAME_MAX);
	if(getcwd(current_dir, FILENAME_MAX) == NULL)
	{
		perror("");
		free(current_dir);
		return 1;
	}
	while(tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD", 6) == 0)
			break;
		tmp = tmp->next;
	}
	// printf("OLDPWD=%s\n", tmp->values[0]);
	if (!tmp)
		return 1;
	get_arg = get_after(s, ' ');
	// printf("get_arg=%s\n", get_arg);
	if (ft_strncmp(get_arg, ".", 1) == 0)
	{
		if (ft_strncmp(get_arg, "..", 2) == 0)
			dot_dot(current_dir, &tmp->values[0]);// CURRENT_DIR || OLDPWD VALUE
		else
			dot();
	}

	return 0;
}