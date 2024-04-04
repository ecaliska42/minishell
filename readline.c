/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/04 15:15:20 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libraries/parsing.h"

int	ft_readline(t_shell *shell, t_parse *command, t_env *envp)
{
	bool	tester = false;
	char	*temp;
	t_exe	execution_utils;

	if (shell == NULL) // temp
	{
		ft_putstr_fd("Error: shell is NULL\n", 2);
		exit(1);
	}
	while (1)
	{
		// shell->input = readline(NULL);
		//interactive 
		if (tester == true)
		{
			if (isatty(fileno(stdin)))
				shell->input = readline(PROMPT);
		}
		else
		{
			temp = readline(PROMPT);
			if (!temp)
			{
				free_environment(&envp);
				//clear_history();
				exit (0);
			}
			shell->input = ft_strdup(temp);
			//free(temp);
			if (!shell->input)
			{
				free_environment(&envp);
				exit (0);
			}
		}
		//non interactive
		if (ft_strlen(shell->input) == 0)
			continue ;
		add_history(shell->input);
		if (lexical_analyzer(shell) == ERROR)
		{
			printf("lexical_analyzer error\n");
			//print_everything(shell);
			ft_putstr_fd("Error: lexical_analyzer\n", 2);
			free_tokens(&shell->tokens);
			free_environment(&envp);//TODO REMOVE
			//free(temp);
			free(shell->input);
			exit(0) ;//todo continue
		}
		if (syntax_check(shell) == SYNTAX_ERROR)
		{
			print_everything(shell);
			printf("syntax_check error\n");
			ft_putstr_fd("Syntax error\n", 2);
			free_tokens(&shell->tokens);
			free_environment(&envp);//TODO REMOVE
			//free(temp);
			free(shell->input);
			exit(0) ;//todo continue
		}
		expansion(shell->tokens, envp, CLOSED);
		prepare_for_execution(&command, &execution_utils, &shell->tokens, &envp);
		// (void)command;
		// (void)execution_utils;
		// print_everything(shell);
		// if (shell->tokens)
		if (shell->input)
		{
			free(shell->input);
			shell->input = NULL;
		}
		free_tokens(&shell->tokens);
	}
	return (SUCCESS);
}
