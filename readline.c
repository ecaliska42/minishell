/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/24 14:29:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "GNL/get_next_line.h"
#include "libraries/parsing.h"

int	ft_readline(t_mini *mini)
{
	bool	tester;
	char	*temp;

	tester = true;
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
			temp = readline(PROMPT);
			if (!temp)
			{
				free_environment(&mini->env);
				clear_history();
				exit(0);
			}
			mini->shell.input = ft_strdup(temp);
			free(temp);
		}
		if (!mini->shell.input)
		{
			// one_function_to_free_them_all(mini);
			// free_environment(&mini->env);
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
				// mini->tokens = NULL;
			}
			free(mini->shell.input);
			mini->shell.input = NULL;
			continue ;
		}
		if (syntax_check(&mini->shell) == SYNTAX_ERROR)
		{
			mini->exit_status = 2;
			free_tokens(&mini->shell.tokens);
			// one_function_to_free_them_all(mini);
			free(mini->shell.input);
			continue ;
		}
		if (mini->shell.tokens)
		{
			expansion(mini->shell.tokens, mini);
			// check all tokens, if at least 1 is not empty, then execute... but be careful about input: "" vs $novar
			// if (mini->shell.tokens->str == )
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
