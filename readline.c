/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/04 21:20:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int ft_readline(t_shell *shell, t_parse *command, t_env *envp)
{
	t_exe	execution_utils;
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
		lexical_analyzer(shell);
		//if ((lexical_analyzer(shell)) == SUCCESS) // error message and everything
		// {
		// 	// parser
		// 	// expand
		// 	// exec
		// }
		prepare_for_execution(&command, &execution_utils, &shell->tokens, &envp);
		print_everything(shell);
		add_history(shell->input);
		free(shell->input);
	}
	return (0);
}