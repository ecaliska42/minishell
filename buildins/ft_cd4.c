/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:49:12 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:51:30 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ch_dir_else(t_env **old, t_env **current, char *now)
{
	(*old)->values = ft_strdup((*current)->values);
	if (!(*old)->values)
		return (free_and_null((void **)&now), ERROR);
	free_and_null((void **)&(*current)->values);
	(*current)->values = malloc(FILENAME_MAX);
	if (!(*current)->values)
		return (free_and_null((void **)&now), ERROR);
	if (!getcwd((*current)->values, FILENAME_MAX))
	{
		perror("CD -: GETCWD");
		return (free_and_null((void **)&now), ERROR);
	}
	printf("%s\n", (*current)->values);
	return (SUCCESS);
}
