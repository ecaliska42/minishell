/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:17:14 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/14 16:54:29 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"


bool ft_is_dollar_nbr(char *c)
{
	if (*c == '$' && ft_isdigit(*c + 1))
		return (true);
	return (false);
}
