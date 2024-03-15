/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/15 14:40:14 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_env(t_env **envp)
{
	//int		i;
	t_env	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("%s=", tmp->name);
		//i = 0;
		printf("%s", tmp->values);
		// while (tmp->values[i])
		// {
		// 	if (!tmp->values[i + 1])
		// 		printf("%s", tmp->values);
		// 	else
		// 		printf("%s:", tmp->values);
		// 	i++;
		// }
		printf("\n");
		tmp = tmp->next;
	}
	tmp = *envp;
	return (0);
}
