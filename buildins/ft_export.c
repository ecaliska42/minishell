/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:07 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/03 15:32:55 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_export(t_env **lst, t_parse **node, t_mini **mini)
{
	t_export	expo;

	expo.i = 1;
	expo.envp = *lst;
	expo.command = *node;
	expo.fail = 0;
	if (array_size(expo.command->command) < 2)
		return (print_export(expo.envp));
	if (expo.command->command[1][0] == '-'
		&& ft_strlen(expo.command->command[1]) > 1)
		return (no_options(mini, expo.command));
	if (while_loop(&expo, mini) == ERROR)
		return (ERROR);
	set_exit_status(expo.fail, mini);
	return (0);
}
