/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 17:44:59 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/09 17:57:56 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_l)
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = new_l;
	else
	{
		temp = *lst;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = new_l;
	}
}
