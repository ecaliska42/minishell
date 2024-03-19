/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/19 20:27:56 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_unset(t_env **head1, t_token **head2)
{
	t_token *token;
	t_env	*envp;

	if (!head1 || !head2)
		return (ERROR);
	token = *head2;
	envp = *head1;
	ft_putendl_fd("IN UNSET", 2);
	return 0;
}