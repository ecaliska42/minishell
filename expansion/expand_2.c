/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:59 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/25 19:30:30 by ecaliska         ###   ########.fr       */
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

t_token	*split_value(char *str, char *value, t_token *token)
{
	char	**words;
	int		i;

	i = 1;
	words = ft_split(value, ' ');
	if (words == NULL)
		return (NULL);
	token->str = ft_strjoin(str, words[0]);
	if (token->str == NULL)
	{
		free_words(words);
		return (NULL);
	}
	while (words[i] != NULL)
	{
		token = create_new_token(words[i], token);
		if (token == NULL)
		{
			free_words(words);
			return (NULL);
		}
		i++;
	}
	free_words(words);
	return (token);
}

char	*add_char(char *str, char new_char)
{
	char	*new;
	int		str_len;

	if (str == NULL)
	{
		new = ft_calloc(2, sizeof(char));
		if (new == NULL)
			return (NULL);
		new[0] = new_char;
		return (new);
	}
	str_len = ft_strlen(str);
	new = ft_calloc(str_len + 2, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str, str_len);
	new[str_len] = new_char;
	free_and_null((void **)&str);
	return (new);
}
