/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:10:00 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/15 17:11:56 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	t_env_size(t_env **envp)
{
	int	i;
	t_env	*tmp;

	i = 0;
	tmp = *envp;	
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

