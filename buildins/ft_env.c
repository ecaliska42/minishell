/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/09 15:12:29 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *envp)
{
	int i = 0;
	while (envp != NULL)
	{
		//printf("\nname is :%s\n", envp->name);
		printf("%s=",envp->name);
		i = 0;
		while (envp->values[i])
		{
			//printf("values are :%s\n", envp->values[i]);
			if (!envp->values[i + 1])
				printf("%s", envp->values[i]);
			else
				printf("%s:", envp->values[i]);
			i++;
		}
		printf("\n");
		envp = envp->next;
	}
	return 0;
}
