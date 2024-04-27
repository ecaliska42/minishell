/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:59 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/27 12:55:20 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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

t_token	*split_value(char *str, char *value, t_token *token, t_expansion *exp)
{
	char	**words;
	char	*joined;

	exp->word_count = 1;
	words = ft_split(value, ' ');
	if (words == NULL)
		return (NULL);
	joined = ft_strjoin(str, words[0]);
	if (str)
		free_and_null((void **)&str);
	if (joined == NULL)
	{
		free_words(words);
		return (NULL);
	}
	token->str = joined;
	token->expanded = 1;
	while (words[exp->word_count] != NULL)
	{
		token = create_new_token(words[exp->word_count], token);
		if (token == NULL)
		{
			free_words(words);
			return (NULL);
		}
		exp->word_count++;
	}
	free_words(words);
	return (token);
}

char	*add_char(char *str, char new_char)
{
	char	*new;
	int		str_len;

	str_len = ft_strlen(str);
	new = ft_calloc(str_len + 2, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str, str_len);
	new[str_len] = new_char;
	free_and_null((void **)&str);
	return (new);
}
