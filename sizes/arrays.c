/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:10:18 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/15 17:42:06 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return 0;
	while (array[i])
		i++;
	return (i);
}

