/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/24 16:39:47 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libraries/parsing.h"

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
			ft_exit();
		if (ft_strlen(shell->input) == 0)
			continue ;
		lexical_analyzer(shell);
		if (syntax_check(shell) == SYNTAX_ERROR)
		{
			print_everything(shell);
			ft_putstr_fd("Syntax error\n", 2);
			free_tokens(&shell->tokens);
			continue;
		}
		expansion(shell->tokens, envp, CLOSED);
		prepare_for_execution(&command, &execution_utils, &shell->tokens, &envp);
		// print_everything(shell);

		// if (shell->tokens)
		add_history(shell->input);
		if (shell->input)
		{
			free(shell->input);
			shell->input = NULL;
		}
		free_tokens(&shell->tokens);
	}
	return (SUCCESS);
}
