/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/08 11:39:34 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *envp)
{
	int i = 0;
	while (envp != NULL)
	{
		printf("\nname is :%s\n", envp->name);
		i = 0;
		while (envp->values[i])
		{
			printf("values are :%s\n", envp->values[i]);
			i++;
		}
		envp = envp->next;
	}
	return 0;
}
