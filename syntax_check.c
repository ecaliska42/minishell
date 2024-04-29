/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:16:58 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 14:13:41 by mesenyur         ###   ########.fr       */
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
			ft_putendl_fd("minishell: syntax error near unexpected token `|'",
				2);
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
			ft_putendl_fd("minishell: syntax error near unexpected token `|'",
				2);
			return (SYNTAX_ERROR);
		}
		tmp = tmp->next;
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

int	invalid_word(t_shell *shell)
{
	t_token	*tmp;

	tmp = shell->tokens;
	while (tmp)
	{
		if (tmp->type != PIPE && tmp->str[0] == '\0')
		{
			ft_putendl_fd("minishell: syntax error", 2);
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
