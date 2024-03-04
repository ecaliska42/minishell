/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:14:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/04 17:28:35 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

//change tokenizing_first_operator to strtok?

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

	i = 0;
	if (!shell || !shell->input) // temp
	{
		ft_putstr_fd("Error: shell->input is NULL\n", 2);
		return(-1);
	}
	if (unclosed_quote_error(shell) == -1)
		return (-1);
	while (shell->input[i] != '\0')
	{
		if (shell->input[i] == '\'' || shell->input[i] == '\"')
			ft_strtok(shell, &i);
		else
			ft_str2tok(shell, &i);
	}

	// while (shell->input[i])
	// {
	// 	if (shell->quotes == CLOSED && (ft_is_space(shell->input[i])))
	// 	{
	// 		i++;
	// 		continue;
	// 	}
	// 	else if (shell->quotes == CLOSED)
	// 	{
	// 		ft_strtok(shell, &i);
	// 	}
	// }
	if (shell->tokens == NULL)
		return (ERROR);
	return (SUCCESS);
}
