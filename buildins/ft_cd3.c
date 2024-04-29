/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:38:38 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:41:26 by ecaliska         ###   ########.fr       */
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
		free_and_null((void **)&s);
		s = ft_strdup("/");
		if (!s)
			return (NULL);
	}
	return (s);
}

int	return_write_free(void *ptr, char *str, int ret)
{
	if (ptr)
		free_and_null((void **)&ptr);
	return_write(str, ret);
	return (ret);
}

int	dot_dot(t_env **old, t_env **current, t_mini *mini)
{
	char	*current_dir;
	char	*change_dir;

	current_dir = malloc(FILENAME_MAX);
	if (!current_dir)
		return (ERROR);
	if (getcwd(current_dir, FILENAME_MAX) == NULL)
	{
		perror("CD..: GETCWD");
		free_and_null((void **)&current_dir);
		return (ERROR);
	}
	change_dir = remove_after_backslash(ft_strdup(current_dir));
	if (!change_dir)
		return (free_and_null((void **)&current_dir), ERROR);
	if ((*old) && (*old)->values)
	{
		free_and_null((void **)&(*old)->values);
		(*old)->values = ft_strdup(current_dir);
		free_and_null((void **)&current_dir);
		check_malloc_exit((*old)->values, mini);
	}
	free_and_null((void **)&current_dir);
	if (chdir(change_dir) == -1)
		return (return_write_free(change_dir, "CD..: CHDIR", ERROR));
	if ((*current) && (*current)->values)
	{
		free_and_null((void **)&(*current)->values);
		(*current)->values = malloc(FILENAME_MAX);
		if (getcwd((*current)->values, FILENAME_MAX) == NULL)
			return_write_free(change_dir, "CD..: GETCWD", ERROR);
		free_and_null((void **)&change_dir);
		return (SUCCESS);
	}
	free_and_null((void **)&change_dir);
	return (SUCCESS);
}
