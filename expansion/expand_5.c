/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:53:59 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 20:49:25 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	*helper_split(t_expansion *exp, char **words, t_token *token)
{
	while (words[exp->word_count] != NULL)
	{
		token = create_new_token(words[exp->word_count], token);
		if (token == NULL)
		{
			free_words(words);
			return (NULL);
		}
		exp->word_count++;
		if (exp->word_count > 0 && token->type != HEREDOC
			&& token->type != RANDOM)
			token->ambiguous = true;
		if (words[exp->word_count] == NULL && exp->split == 1)
		{
			token = create_new_token("", token);
			exp->split = 0;
			if (token == NULL)
			{
				free_words(words);
				return (NULL);
			}
		}
	}
	return (token);
}

static void	*val_check(void *ptr, char **words)
{
	if (ptr == NULL)
	{
		free_words(words);
		return (NULL);
	}
	return (ptr);
}

char	*check_join(t_expansion *exp, char *str, char **words, t_token *token)
{
	char	*joined;

	joined = NULL;
	if (exp->join == 1 || exp->replace == 1)
	{
		joined = ft_strjoin(str, words[0]);
		if (joined == NULL)
		{
			exp->exit = 1;
			free_words(words);
			return (NULL);
		}
		exp->word_count++;
		if (str)
			free_and_null((void **)&str);
		val_check(joined, words);
		if (joined)
			token->str = joined;
	}
	return (token->str);
}

static void	check_words(char **words, t_expansion *exp, t_token *token)
{
	if (words[exp->word_count] == NULL && exp->split == 1)
	{
		token = create_new_token("", token);
		exp->split = 0;
		val_check(token, words);
	}
}

t_token	*split_value(char *str, char *value, t_token *token, t_expansion *exp)
{
	char	**words;

	exp->word_count = 0;
	if ((ft_is_white_space(exp->value[ft_strlen(exp->value) - 1])
			&& *exp->tmp_i != '\0'))
		exp->split = 1;
	words = ft_split(value, ' ');
	if (words == NULL)
		return (NULL);
	if (words[0] == NULL)
	{
		free_words(words);
		if (token->str[0] != '\0')
			token = create_new_token("", token);
		return (token);
	}
	token->str = check_join(exp, str, words, token);
	if (exp->exit == 1)
		return (NULL);
	token->expanded = 1;
	check_words(words, exp, token);
	token = helper_split(exp, words, token);
	val_check(token, words);
	free_words(words);
	return (token);
}
