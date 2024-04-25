/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/25 11:34:02 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "GNL/get_next_line.h"
#include "libraries/parsing.h"

int	ft_readline(t_mini *mini)
{
	bool	tester;

	tester = false;
	mini->exit_status = 0;
	while (1)
	{
		signal_handler(1, mini);
		if (tester == true)
		{
			if (isatty(fileno(stdin)))
				mini->shell.input = readline(PROMPT);
			else
			{
				char *line = get_next_line(fileno(stdin));
				mini->shell.input = ft_strtrim(line, "\n");
				free(line);
			}
		}
		else
		{
			mini->shell.input = readline(PROMPT);
			if (!mini->shell.input)
			{
				free_mini_and_exit(&mini);
				clear_history();
				exit(mini->exit_status);
			}
		}
		if (!mini->shell.input)
		{
			free_mini_and_exit(&mini);
			clear_history();
			exit(mini->exit_status);
		}
		signal_handler(3, mini);
		if (ft_strlen(mini->shell.input) == 0)
			continue ;
		add_history(mini->shell.input);
		if (lexical_analyzer(&mini->shell) == ERROR)
		{
			mini->exit_status = 2;
			if (mini->shell.tokens != NULL)
			{
				free_tokens(&mini->shell.tokens);
				mini->shell.tokens = NULL;
			}
			free(mini->shell.input);
			mini->shell.input = NULL;
			continue ;
		}
		if (syntax_check(&mini->shell) == SYNTAX_ERROR)
		{
			mini->exit_status = 2;
			free_tokens(&mini->shell.tokens);
			free(mini->shell.input);
			continue ;
		}
		if (mini->shell.tokens)
		{
			expansion(mini->shell.tokens, mini);
			if (prepare_for_execution(&mini) == ERROR)
			{
				ft_putstr_fd("Error: prepare_for_execution\n", 2);
				free_tokens(&mini->shell.tokens);
				free(mini->shell.input);
				exit(1);
			}

		}
		if (mini->shell.input)
		{
			free(mini->shell.input);
			mini->shell.input = NULL;
		}
		free_tokens(&mini->shell.tokens);
	}
	return (SUCCESS);
}
