/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/16 12:54:57 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libraries/parsing.h"

#include "GNL/get_next_line.h"

int	ft_readline(t_mini *mini)//(t_shell *shell, t_parse *command, t_env *envp)//(t_mini *mini)//
{
	bool	tester = true;
	char	*temp;
	mini->exit_status = 0;

	// if (shell == NULL) // temp
	// {
	// 	ft_putstr_fd("Error: shell is NULL\n", 2);
	// 	exit(1);
	// }
	while (1)
	{
		signal_handler(1);
		if (tester == true)
		{
			if (isatty(fileno(stdin)))
				mini->shell.input = readline(PROMPT);
			else
			{
				char *line;
				line = get_next_line(fileno(stdin));
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
				//clear_history();
				exit (0);
			}
			mini->shell.input = ft_strdup(temp);
			free(temp);
		}
		if (!mini->shell.input)
		{
			// one_function_to_free_them_all(mini);
			free_environment(&mini->env);
			exit (mini->exit_status);
		}
		signal_handler(3);
		if (ft_strlen(mini->shell.input) == 0)
			continue ;
		add_history(mini->shell.input);
		if (lexical_analyzer(&mini->shell) == ERROR)
		{
			// printf("lexical_analyzer error\n");
			// print_everything(shell);
			mini->exit_status = 2;
			ft_putstr_fd("Error: lexical_analyzer\n", 2);
			free_tokens(&mini->shell.tokens);
			free(mini->shell.input);
			continue;
		}
		if (syntax_check(&mini->shell) == SYNTAX_ERROR)
		{
			mini->exit_status = 2;
			// print_everything(shell);
			// printf("syntax_check error\n");
			ft_putstr_fd("Syntax error\n", 2);
			free_tokens(&mini->shell.tokens);
			free(mini->shell.input);
			continue;
		}
		if (mini->shell.tokens)
		{
			expansion(mini->shell.tokens, mini);
			if (prepare_for_execution(&mini) == ERROR)
			{
				// print_everything(shell);
				ft_putstr_fd("Error: prepare_for_execution\n", 2);
				free_tokens(&mini->shell.tokens);
				free(mini->shell.input);
				exit (1);
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
