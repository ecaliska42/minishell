/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:08 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/16 20:04:54 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_exit(void)
{
	ft_putendl_fd("IN EXIT", 2);
	ft_putstr_fd("exiting minishell\n", 1);
	exit(0);
	return 0;
}