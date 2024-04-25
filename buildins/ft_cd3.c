/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:38:38 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/25 15:23:32 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*remove_after_backslash(char *s)
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

int	dot_dot(t_env **old, t_env **current)
{
	char	*current_dir;
	char	*change_dir;

	current_dir = malloc(FILENAME_MAX);
	getcwd(current_dir, FILENAME_MAX);
	change_dir = remove_after_backslash(ft_strdup(current_dir));
	if ((*old) && (*old)->values)
	{
		free((*old)->values);
		(*old)->values = ft_strdup(current_dir);
		free_and_null((void **)&current_dir);
	}
	if ((*current) && (*current)->values)
	{
		if (chdir(change_dir) == -1)
			return_write("CD..: CHDIR", ERROR);
		free((*current)->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (getcwd((*current)->values, FILENAME_MAX) == NULL)
			return_write("CD..: GETCWD", ERROR);
		free_and_null((void **)&change_dir);
		return (SUCCESS);
	}
	else
		if (chdir(change_dir) == -1)
		{
			free_and_null((void **)&change_dir);
			return_write("CD..: CHDIR", ERROR);
		}
	free_and_null((void **)&change_dir);
	return (SUCCESS);
}
