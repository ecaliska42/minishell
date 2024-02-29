/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:03:33 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/28 18:00:04 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tokenizing_first_operator(char *str, t_shell *shell)
{
	if (!str || !shell || !shell->tokens)
		return (0);
	if (*str == '|' && !shell->tokens->type)
		shell->tokens->type = PIPE;
	else if (*str == '<' && *(str + 1) != '<' && !shell->tokens->type)
		shell->tokens->type = INPUT;
	else if (*str == '>' && *(str + 1) != '>' && !shell->tokens->type)
		shell->tokens->type = TRUNC;
	else if (*str == '>' && *(str + 1) == '>' && !shell->tokens->type)
	{
		// *inc += 1;
		shell->tokens->type = APPEND;
	}
	else if (*str == '<' && *(str + 1) == '<' && !shell->tokens)
	{
		// *inc += 1;
		shell->tokens->type = HEREDOC;
	}
	if (shell->tokens->type)
		return (1);
	return (0);
}

void ft_tokenizer(t_shell *shell, int *i)
{
	char *copy;

	copy = shell->input;
	if (copy[*i] == '|')
		shell->tokens->type = PIPE;
	else if (copy[*i] == '>' && copy[(*i) + 1] == '>')
		shell->tokens->type = APPEND;
	else if (copy[*i] == '<' && copy[(*i) + 1] == '<')
		shell->tokens->type = HEREDOC;
	else if (copy[*i] == '>')
		shell->tokens->type = TRUNC;
	else if (copy[*i] == '<')
		shell->tokens->type = INPUT;
	else
		shell->tokens->type = RANDOM;

}