/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needed_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:32:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/01 15:50:30 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool ft_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

bool ft_is_dollar(char c)
{
	if (c == '$')
		return (true);
	return (false);
}

bool ft_is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

bool ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool ft_is_redirection(t_tokentype type)
{
	if (type == APPEND || type == TRUNC
		|| type == INPUT || type == HEREDOC)
		return (true);
	return (false);
}

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
	//*tokens = new;
	return (0);
}

void ft_tokenizer(t_shell *shell, t_token *last, int i)
{
	char *copy;

	copy = shell->input;

	if (copy[i] == '|')
		last->type = PIPE;
	else if (copy[i] == '>' && copy[i + 1] == '>')
		last->type = APPEND;
	else if (copy[i] == '<' && copy[i + 1] == '<')
		last->type = HEREDOC;
	else if (copy[i] == '>')
		last->type = TRUNC;
	else if (copy[i] == '<')
		last->type = INPUT;
	else
		last->type = RANDOM;
}


// bool ft_is_redout(t_shell *shell)
// {
// 	if (shell->tokens->type == APPEND || shell->tokens->type == TRUNC)
// 		return (true);
// 	return (false);
// }

// char *get_outfile(t_shell *shell)
// {
// 	t_token *token;
// 	char *word;

// 	token = shell->tokens;
// 	if (ft_is_redout(shell))
// 	{
// 		if (token->next)
// 		{
// 			word = malloc(ft_strlen(token->next->str) + 1);
// 			if (!word)
// 			{
// 				perror("failed alloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			strcpy(word, token->next->str); //change ft


// 		return (word);
// 		}
// 		token = token->next;
// 	}
// 	return (NULL);
// }

// bool ft_is_redin(t_shell *shell)
// {
// 	if (shell->tokens->type == INPUT || shell->tokens->type == HEREDOC)
// 		return (true);
// 	return (false);
// }

// char *get_infile(t_shell *shell)
// {
// 	t_token *token;
// 	char *word;

// 	token = shell->tokens;
// 	if (ft_is_redin(shell))
// 	{
// 		if (token->next)
// 		{
// 			word = malloc(ft_strlen(token->next->str) + 1);
// 			if (!word)
// 			{
// 				perror("failed alloc");
// 				exit(EXIT_FAILURE);
// 			}
// 			strcpy(word, token->next->str); //change ft
// 			return (word);
// 		}
// 		token = token->next;
// 	}
// 	return (NULL);
// }
