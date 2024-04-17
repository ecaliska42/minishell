/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:16:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/17 17:32:17 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"
#include "libft/libft.h"

int	pipe_valid(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && !tmp->next)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	too_many_pipes(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type == PIPE && tmp->next && tmp->next->type == PIPE)
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	three_outputs(t_shell *shell)
{
	char *input;
	int i;

	i = 0;
	input = shell->input;
	while (input[i])
	{
		if (input[i] == '>' && input[i + 1] && input[i + 1] == '>' && input[i + 2] && input[i + 2] == '>')
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `>>'", 2);
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (0);
}

int	three_inputs(t_shell *shell)
{
	char *input;
	int i;

	i = 0;
	input = shell->input;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] && input[i + 1] == '<' && input[i + 2] && input[i + 2] == '<')
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `>>'", 2);
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (0);
}

int it_is_redirection(char c)
{
	if (c == '>' || c == '<')
		return (true);
	return (false);
}

int	redir_pipe(t_shell *shell)
{
	int	i;
	char *input;
	
	input = shell->input;
	i = 0;
	while (input[i] != '\0')
	{
		if (it_is_redirection(input[i]) == true)
		{
			i++;
			skip_spaces(input, &i);
			if (input[i] == '|')
			{
				ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
				return (SYNTAX_ERROR);
			}
		}
		i++;
	}
	return (0);
}

int	pipe_start(t_shell *shell)
{
	int	i;

	i = 0;
	skip_spaces(shell->input, &i);
	if (shell->input[i] && shell->input[i] == '|')
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
		return (SYNTAX_ERROR);
	}
	return (0);
}

// int	wrong_order(t_shell *shell)
// {
// 	char *input;
// 	int i;

// 	i = 0;
// 	input = shell->input;
// 	while (input[i])
// 	{
// 		if (input[i] == '>') // && input[i + 1] && input[i + 1] == '<')
// 		{
// 			i++;
// 			skip_spaces(input, &i);
// 			if (input[i] == '<')
// 			{
// 				ft_putendl_fd("minishell: syntax error near unexpected token `<'", 2);
// 				return (SYNTAX_ERROR);
// 			}
// 		}
// 		if (input[i] == '<') // && input[i + 1] && input[i + 1] == '<')
// 		{
// 			i++;
// 			skip_spaces(input, &i);
// 			if (input[i] == '>')
// 			{
// 				ft_putendl_fd("minishell: syntax error near unexpected token `>'", 2);
// 				return (SYNTAX_ERROR);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	invalid_word(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->str[0] == '\0')
		{
			ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	syntax_check(t_shell *shell)
{
	if (pipe_start(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (pipe_valid(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (too_many_pipes(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	if (invalid_word(shell) == SYNTAX_ERROR)
		return (SYNTAX_ERROR);
	return (0);
}

// int syntax_before_token(t_shell *shell)
// {
// 	if (three_outputs(shell) == SYNTAX_ERROR)
// 		return (SYNTAX_ERROR);
// 	if (three_inputs(shell) == SYNTAX_ERROR)
// 		return (SYNTAX_ERROR);
// 	if (wrong_order(shell) == SYNTAX_ERROR)
// 		return (SYNTAX_ERROR);
// 	if (redir_pipe(shell) == SYNTAX_ERROR)
// 		return (SYNTAX_ERROR);
// 	return (0);
// }