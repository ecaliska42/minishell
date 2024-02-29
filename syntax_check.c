/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:16:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/26 18:17:59 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// int	three_pipes(t_shell *shell)
// {
// 	t_token	*tmp;

// 	tmp = shell->tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE && tmp->next->next && tmp->next->next->type == PIPE)
// 		{
// 			printf("minishell: syntax error near unexpected token `||'\n");
// 			return (1);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

int pipe_valid(t_shell *shell, char *input) // after pipe no command
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int too_many_pipes(t_shell *shell, char *s) // || is not allowed
{
	int i;
	char *tmp;

	i = 0;
	tmp = shell->input;
	while (tmp[i])
	{
		if (tmp[i] == '|' && tmp[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `||'\n");
			return (2);
		}
		i++;
	}
	return (0);
}

// int three_truncs(t_shell *shell)
// {
// 	t_token	*tmp;

// 	tmp = shell->tokens;
// 	while (tmp)
// 	{
// 		if (tmp->type == TRUNC && tmp->next && tmp->next->type == TRUNC && tmp->next->next && tmp->next->next->type == TRUNC)
// 		{
// 			printf("minishell: syntax error near unexpected token `>>'\n");
// 			return (SYNTAX_ERROR);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

int three_truncs(t_shell *shell, char *s) // >>> is not allowed
{
	int i;
	char *tmp;

	i = 0;
	tmp = shell->input;
	while (tmp[i])
	{
		if (tmp[i] == '>' && tmp[i + 1] == '>' && tmp[i + 2] == '>')
		{
			printf("minishell: syntax error near unexpected token `>>'\n");
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (0);
}

int three_inputs(t_shell *shell, char *s) // <<< is not allowed
{
	int i;
	char *tmp;

	i = 0;
	tmp = shell->input;
	while (tmp[i])
	{
		if (tmp[i] == '<' && tmp[i + 1] == '<' && tmp[i + 2] == '<')
		{
			printf("minishell: syntax error near unexpected token `<<<'\n");
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (0);
}

int syntax_check(t_shell *shell) // check for syntax errors
{
	if (pipe_valid(shell, shell->input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (too_many_pipes(shell, shell->input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (three_truncs(shell, shell->input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (three_inputs(shell, shell->input) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (0);
}
