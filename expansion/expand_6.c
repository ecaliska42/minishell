/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:29:12 by mesenyur          #+#    #+#             */
/*   Updated: 2024/05/01 14:48:53 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*add_char(char *str, char new_char)//!LEAK IF ADD_CHAR FAILS
{
	char	*new;
	int		str_len;

	str_len = ft_strlen(str);
	new = ft_calloc(str_len + 2, sizeof(char));
	if (new == NULL)
		return (free_and_null((void **)&str), NULL);
	ft_memcpy(new, str, str_len);
	new[str_len] = new_char;
	free_and_null((void **)&str);
	return (new);
}

char	*replace_exit_code(char *str, char **new, int *i, t_mini *ms)
{
	char	*new_str;
	char	*exit_code;

	if (str[*i] && str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '?')
	{
		exit_code = ft_itoa(ms->exit_status);
		free_expansion(exit_code, ms->exp, ms);
		(*i) += 2;
		new_str = ft_strjoin(*new, exit_code);
		free_and_null((void **)&exit_code);
		free_and_null((void **)new);
		free_expansion(new_str, ms->exp, ms);
		*new = new_str;
		return (*new);
	}
	return (0);
}

t_token	*create_new_token(char *word, t_token *last)
{
	t_token	*new;

	if (!word || !last)
		return (NULL);
	new = ft_calloc(1, sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(word);
	if (new->str == NULL)
	{
		free_and_null((void **)&new);
		return (NULL);
	}
	new->next = last->next;
	new->type = last->type;
	last->next = new;
	last->expanded = 1;
	new->expanded = 1;
	return (new);
}

void	free_words(char **words)
{
	int	i;

	i = 0;
	if (!words)
		return ;
	while (words[i] != NULL)
	{
		free_and_null((void **)&words[i]);
		i++;
	}
	free_and_null((void **)&words);
}

void	expansion(t_token *token, t_mini *ms)
{
	t_expansion	exp;

	ms->exp = &exp;
	ft_bzero(&exp, sizeof(t_expansion));
	while (token != NULL)
	{
		if (token->str && token->expanded == 0)
			token = expand_variable(exp, token, ms);
		if (token)
			token = token->next;
	}
}
