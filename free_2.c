/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:14:17 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/26 10:38:28 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_and_null((void **)&str[i]);
		i++;
	}
	free_and_null((void **)&str);
}

void	check_int_exit(t_mini **mini, int n, int cond, char *str)
{
	if (n != cond)
		return ;
	ft_putendl_fd(str, 2);
	free_mini_and_exit(mini);
}