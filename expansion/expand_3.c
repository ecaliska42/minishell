/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/26 16:16:58 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	handle_heredoc_exp(t_token *token, t_expansion *exp, char *str, t_mini *ms)
{
	if (token->type == HEREDOC)
	{
		token->flag_exp = true;
		while (str[exp->i++])
		{
			if (str[exp->i] == '\"' || str[exp->i] == '\'')
				token->flag_exp = false;
		}
		exp->i = 0;
		exp->new_str = expand_heredoc_delimeter(exp->new_str, str, &exp->i, ms);
		if (!exp->new_str)
			return (-1);
	}
	return (0);
}

void	help_norm(t_expansion *exp, t_mini *ms, t_token **last_token)
{
	(*last_token)->str = add_char((*last_token)->str, *exp->tmp_i);
	free_expansion((*last_token)->str, ms->exp, ms);
	exp->i++;
	exp->tmp_i++;
}

t_token	*handle_splitting(t_expansion *exp, t_token *token,
		t_token **last_token, t_mini *ms)
{
	char *ptr;

	if (token->type != HEREDOC && token->type != RANDOM)
		token->ambiguous = true;
	exp->tmp_i = &exp->joker[exp->i];
	(*last_token) = split_value(exp->new_str, exp->value, token);
	free_expansion(last_token, ms->exp, ms);
	if (*exp->tmp_i)
	{
		while (*exp->tmp_i && *exp->tmp_i != '$' && *exp->tmp_i != '\"'
			&& *exp->tmp_i != '\'')
			help_norm(exp, ms, last_token);
		ptr = exp->new_str;
		exp->new_str = ft_strdup((*last_token)->str);
		free(ptr);
		if (ft_is_dollar(*exp->tmp_i) || *exp->tmp_i == '\"'
			|| *exp->tmp_i == '\'')
		{
			token = *last_token;
			return (NULL);
		}
		else
			return (*last_token);
	}
	token = *last_token;
	return (*last_token);
}

void	shorten_exp(t_expansion *exp, t_mini *ms)
{
	char	*tmp;

	tmp = ft_strjoin(exp->new_str, exp->value);
	free_and_null((void **)&exp->new_str);
	free_expansion(tmp, ms->exp, ms);
	free_and_null((void **)&exp->value);
	exp->new_str = tmp;
}

t_token	*handle_expansion(t_token *token, t_expansion *exp, t_mini *ms)
{
	t_token	*last_token;
	t_token	*ret;

	last_token = NULL;
	do_expand(exp->joker, exp, ms);
	if (exp->value != NULL)
	{
		if (exp->value[0] == '\0')
			token->ambiguous = true;
		exp->value = ft_strtrim(exp->value, " ");
		if (!exp->value)
			return (NULL);
		if (ft_strchr(exp->value, ' ') == NULL)
			shorten_exp(exp, ms);
		else
		{
			ret = handle_splitting(exp, token, &last_token, ms);
			if (ret)//CHANGED CAUSED MEMORY LEAKS
			{
				free_and_null((void **)&exp->value);
				return (ret);
			}
		}
	}
	else
		token->empty = true;
	return (NULL);
}
