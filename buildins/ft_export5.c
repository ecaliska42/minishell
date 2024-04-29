/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:40:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 16:52:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	do_while_export(t_env *tmp, t_env **copy, t_env *node)
{
	if (tmp->values)
	{
		node->values = ft_strdup(tmp->values);
		if (!node->values)
		{
			free_and_null((void **)&node->name);
			free_and_null((void **)&node);
			return (ERROR);
		}
	}
	else
		node->values = NULL;
	node->next = NULL;
	tenv_add_back(&copy, node);
	return (SUCCESS);
}
