/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/07 17:25:46 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *envp)
{
	while (envp->next != NULL)
	{
		printf("name is : %s\n", envp->name);
		printf("value is : %s\n\n", envp->name);
		envp= envp->next;
	}
	return 0;
}
