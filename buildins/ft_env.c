/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/30 19:30:56 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_env(t_env **envp, t_mini **mini, t_parse **node)
{
	t_env	*tmp;

	tmp = *envp;
	if (array_size((*node)->command) >= 2)
	{
		write(2, "env: No such file or directory\n", 24);
		(*mini)->exit_status = 127;
		return (SUCCESS);
	}
	while (tmp != NULL)
	{
		if (tmp->values != NULL)
			printf("%s=%s\n", tmp->name, tmp->values);
		tmp = tmp->next;
	}
	tmp = *envp;
	(*mini)->exit_status = 0;
	return (SUCCESS);
}
