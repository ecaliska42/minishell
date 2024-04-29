/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:17:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:17:31 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void	*dup_for_no_pipes(t_parse *comm)
{
	if (comm->infd > 0)
	{
		if (dup2(comm->infd, STDIN_FILENO) == -1)
			return (NULL);
		close(comm->infd);
	}
	if (comm->outfd > 0)
	{
		if (dup2(comm->outfd, STDOUT_FILENO) == -1)
			return (NULL);
		close(comm->outfd);
	}
	return ((void *)1);
}
