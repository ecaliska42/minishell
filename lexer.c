/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:14:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/16 06:18:02 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"
#include <stdlib.h>

int unclosed_quote_error(t_shell *shell)
{
	int i;

	i = 0;
	shell->quotes = CLOSED;
	if (!shell->input)
	{
		ft_putstr_fd("Error: input is NULL\n", 2);
		return(-1);
	}
	while (shell->input[i] != '\0')
	{
		quote_check(shell->input[i], &shell->quotes);
		i++;
	}
	if (!(shell->quotes == CLOSED))
	{
		ft_putstr_fd("minishell: unclosed quote\n", 2);
		return (-1);
	}
	return (0);
}



int	lexical_analyzer(t_shell *shell)
{
	int	i;
	// t_token	*last_token;

	i = 0;
	// last_token = NULL;
	if (!shell || !shell->input) // temp
	{
		ft_putstr_fd("Error: shell->input is NULL\n", 2);
		return(-1);
	}
	if (unclosed_quote_error(shell) == -1)
		exit(1);
	shell->quotes = CLOSED;
	while (shell->input[i] != '\0')
	{
			ft_strtok(shell, &i);
	}
	if (shell->tokens == NULL)
		return (ERROR);
	return (SUCCESS);
}
