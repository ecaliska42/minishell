/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:50 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 16:37:09 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/parsing.h"

t_token	*add_new_empty_token(t_shell *shell)
{
	t_token	*last_token;

	if (token_add(&shell->tokens) == -1)
	{
		ft_putendl_fd("Error: Token add failed", 2);
		return (NULL);
	}
	last_token = get_last_token(&shell->tokens);
	return (last_token);
}
