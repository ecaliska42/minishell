/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:16:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/08 14:31:43 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int pipe_valid(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
		{
			printf("pipe_valid\n");
			printf("minishell: syntax error near unexpected token `|'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int too_many_pipes(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			printf("too_many_pipes\n");
			printf("minishell: syntax error near unexpected token `|'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int three_outputs(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == OUTPUT && tmp->next && tmp->next->type == APPEND)
		{
			printf("three_outputs\n");
			printf("minishell: syntax error near unexpected token `>>'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int three_inputs(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == INPUT && tmp->next && tmp->next->type == HEREDOC)
		{
			printf("three_inputs\n");
			printf("minishell: syntax error near unexpected token `>>'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int redir_pipe(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if ((ft_is_redirection(tmp->type) == true) && tmp->next && tmp->next->type == PIPE)
		{
			printf("redir_pipe\n");
			printf("minishell: syntax error near unexpected token `|'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int syntax_check(t_shell *shell)
{
	if (shell->tokens->type == PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (SYNTAX_ERROR);
	}
	if (pipe_valid(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (too_many_pipes(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (three_outputs(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (three_inputs(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (redir_pipe(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);

	return (0);
}