/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/28 16:29:36 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **envp)
{
	int i = 0;
	t_env	*tmp;

	tmp = *envp;
	while (tmp != NULL)
	{
		printf("%s=",tmp->name);
		i = 0;
		while (tmp->values[i])
		{
			if (!tmp->values[i + 1])
				printf("%s", tmp->values[i]);
			else
				printf("%s:", tmp->values[i]);
			i++;
		}
		printf("\n");
		tmp = tmp->next;
	}
	tmp = *envp;
	return 0;
}
