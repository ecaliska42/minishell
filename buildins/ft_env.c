/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:10 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/11 16:18:50 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_env(t_env **envp, t_mini **mini, t_parse **node)
{
	//ft_putendl_fd("IN ENV", 2);
	t_env	*tmp;

	tmp = *envp;
	if (array_size((*node)->command) > 2)
	{
		write(2, "env: No such file or directory\n", 24);
		(*mini)->exit_status = 1;
		return (1);
	}
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->name, tmp->values);
		tmp = tmp->next;
	}
	tmp = *envp;
	(*mini)->exit_status = 0;
	return (0);
}
