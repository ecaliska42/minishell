/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/15 21:50:32 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

void	remove_quotes(t_shell *shell)
{
	(void)shell;
	return ;
}

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
		if (!shell->input || ft_strlen(shell->input) == 0)
			continue ;
		lexical_analyzer(shell);
		if (syntax_check(shell) == SYNTAX_ERROR)
		{
			ft_putstr_fd("Syntax error\n", 2);
			continue;
		}
		expand_variable(shell->tokens, envp);
		// remove_quotes(shell); //? remove quotes function
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
	return (0);
}
