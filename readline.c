/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/28 20:28:39 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libraries/parsing.h"

int ft_readline(t_shell *shell, t_parse *command, t_env *envp)
{
	bool	tester = false;
	t_exe	execution_utils;
	if (shell == NULL) // temp
	{
		ft_putstr_fd("Error: shell is NULL\n", 2);
		exit(1);
	}
	while (1)
	{
		// shell->input = readline(NULL);
		if (tester == true)
		{
			if (isatty(fileno(stdin)))
				shell->input = readline(PROMPT);
		}
		else
		{
			shell->input = readline(PROMPT);
			if (!shell->input)
			{
				free_environment(&envp);
				exit (0);
			}
		}
		if (!shell->input)
			exit (0);//TODO EXITCODE
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
