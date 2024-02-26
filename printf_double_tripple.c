/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_double_tripple.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:49:02 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/26 13:51:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_double(char **str)
{
	int	i;
	
	i = 0;
	while(str[i])
	{
		printf("%d is %s\n", i, str[i]);
		i++;
	}
}

void	printf_tripple(char ***str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while(str[i])
	{
		j = 0;
		while (str[i][j])
		{
			printf("%d is %s\n", i, str[i][j]);
			j++;
		}
		i++;
	}
}