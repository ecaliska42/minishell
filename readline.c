/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/28 19:00:01 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int ft_readline(t_shell *shell)
{
		printf("shell->quotes: %d\n", shell->quotes);
	
	if (shell == NULL) // temp
	{
		ft_putstr_fd("Error: shell is NULL\n", 2);
		exit(1);
	}
	while (1)
	{
		shell->input = readline(PROMPT);
		if (!shell->input)
			return (0);
		printf("shell->quotes: %d\n", shell->quotes);
		lexical_analyzer(shell);
		//if ((lexical_analyzer(shell)) == SUCCESS) // error message and everything
		// {
		// 	// parser
		// 	// expand
		// 	// exec
		// }
		print_everything(shell);
		add_history(shell->input);
		free(shell->input);
	}
	return (0);
}