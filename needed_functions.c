/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needed_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:32:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/16 16:07:17 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"

t_token *get_last_token(t_token **tokens)
{
	t_token *tmp;

	tmp = *tokens;
	if (!tmp)
	{
		return (NULL);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

int token_add(t_token **tokens)
{
	t_token *new;
	t_token *tmp;

	tmp = *tokens;
	new = malloc(sizeof(t_token));
	if (!new)
	{
		perror("failed malloc");
		return (-1);
	}
	ft_bzero(new, sizeof(t_token));
	if (tmp == NULL)
	{
		*tokens = new;
		return (0);
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	return (0);
}

void ft_tokenizer(t_shell *shell, t_token *last, int i)
{
	char *copy;

	copy = shell->input;

	if (copy[i] == '|')
		last->type = PIPE;
	else if (copy[i] == '>' && copy[i + 1] != '\0' && copy[i + 1] == '>' && (copy[i + 2] == '\0' || copy[i + 2] != '>'))
		last->type = APPEND;
	else if (copy[i] == '<' && copy[i + 1] != '\0' && copy[i + 1] == '<' && (copy[i + 2] == '\0' || copy[i + 2] != '<'))
		last->type = HEREDOC;
	else if (copy[i] == '>')
		last->type = OUTPUT;
	else if (copy[i] == '<')
		last->type = INPUT;
	else
		last->type = RANDOM;
}
