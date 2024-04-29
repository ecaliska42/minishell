/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:12:54 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 18:20:04 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "GNL/get_next_line.h"
#include "libft/libft.h"
#include "libraries/parsing.h"

void	first_stage(t_mini *mini)
{
	signal_handler(1, mini);
	mini->shell.input = readline(PROMPT);
	if (!mini->shell.input)
	{
		clear_history();
		free_mini_and_exit(&mini);
		exit(mini->exit_status);
	}
	if (!mini->shell.input)
	{
		free_mini_and_exit(&mini);
		clear_history();
		exit(mini->exit_status);
	}
}

int	second_stage(t_mini *mini)
{
	if (lexical_analyzer(&mini->shell) == ERROR)
	{
		mini->exit_status = 2;
		if (mini->shell.tokens != NULL)
		{
			free_tokens(&mini->shell.tokens);
			mini->shell.tokens = NULL;
		}
		free_and_null((void **)&mini->shell.input);
		mini->shell.input = NULL;
		return (1);
	}
	return (0);
}

int	third_stage(t_mini *mini)
{
	if (syntax_check(&mini->shell) == SYNTAX_ERROR)
	{
		mini->exit_status = 2;
		free_tokens(&mini->shell.tokens);
		free_and_null((void **)&mini->shell.input);
		return (1);
	}
	return (0);
}

void	fourth_stage(t_mini *mini)
{
	expansion(mini->shell.tokens, mini);
	if (prepare_for_execution(&mini) == ERROR)
	{
		if (g_sig)
			free_mini(&mini);
		ft_putstr_fd("Error: prepare_for_execution\n", 2);
		free_tokens(&mini->shell.tokens);
		free_and_null((void **)&mini->shell.input);
		exit(1);
	}
	if (g_sig)
		free_mini(&mini);
}

int	ft_readline(t_mini *mini)
{
	mini->exit_status = 0;
	while (1)
	{
		first_stage(mini);
		signal_handler(3, mini);
		if (ft_strlen(mini->shell.input) == 0)
			continue ;
		add_history(mini->shell.input);
		if (second_stage(mini))
			continue ;
		if (third_stage(mini))
			continue ;
		if (mini->shell.tokens)
			fourth_stage(mini);
		if (mini->shell.input)
		{
			free_and_null((void **)&mini->shell.input);
			mini->shell.input = NULL;
		}
		free_tokens(&mini->shell.tokens);
	}
	return (SUCCESS);
}
