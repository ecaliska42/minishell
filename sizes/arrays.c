/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/15 21:40:12 by mesenyur         ###   ########.fr       */
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
