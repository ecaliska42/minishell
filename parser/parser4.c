/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:11:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:11:22 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	add_back(t_parse **com, t_parse *node)
{
	t_parse	*temp;

	if (*com == NULL)
		*com = node;
	else
	{
		temp = *com;
		while (temp -> next != NULL)
			temp = temp -> next;
		temp -> next = node;
	}
	temp = *com;
}
