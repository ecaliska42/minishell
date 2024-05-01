/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needed_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:32:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/05/01 15:32:35 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"
#include "libraries/minishell.h"

t_token	*get_last_token(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	token_add(t_token **tokens, t_mini *ms)
{
	t_token	*new;
	t_token	*tmp;

	tmp = *tokens;
	new = ft_calloc(1, sizeof(t_token));
	check_malloc_exit(new, ms);
	ft_bzero(new, sizeof(t_token));
	if (tmp == NULL)
	{
		*tokens = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

void	ft_tokenizer(t_shell *shell, t_token *last, int i)
{
	char	*copy;

	copy = shell->input;
	if (copy[i] == '|')
		last->type = PIPE;
	else if (copy[i] == '>' && copy[i + 1] != '\0' && copy[i + 1] == '>'
		&& (copy[i + 2] == '\0' || copy[i + 2] != '>'))
		last->type = APPEND;
	else if (copy[i] == '<' && copy[i + 1] != '\0' && copy[i + 1] == '<'
		&& (copy[i + 2] == '\0' || copy[i + 2] != '<'))
		last->type = HEREDOC;
	else if (copy[i] == '>')
		last->type = OUTPUT;
	else if (copy[i] == '<')
		last->type = INPUT;
	else
		last->type = RANDOM;
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] != '\0' && ft_is_space(line[*i]) == true)
		(*i)++;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
