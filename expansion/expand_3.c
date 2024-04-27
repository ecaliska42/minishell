/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/27 11:36:01 by mesenyur         ###   ########.fr       */
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
		token->str = expand_heredoc_delimeter(token->str, str, &exp->i, ms);
		if (!token->str)
			return (-1);
		
	}
	return (0);
}

void	help_norm(t_expansion *exp, t_mini *ms, t_token *last_token)
{
	last_token->str = add_char(last_token->str, *exp->tmp_i);
	free_expansion(last_token->str, ms->exp, ms);
	exp->i++;
	exp->tmp_i++;
}

t_token	*handle_splitting(t_expansion *exp, t_token *token,
		t_token *last_token, t_mini *ms)
{
	if (token->type != HEREDOC && token->type != RANDOM)
		token->ambiguous = true;
	exp->tmp_i = &exp->joker[exp->i];
	last_token = split_value(token->str, exp->value, token, exp);
	free_expansion(last_token, ms->exp, ms);
	last_token->expanded = 1;
	if (*exp->tmp_i)
	{
		while (*exp->tmp_i && *exp->tmp_i != '$' && *exp->tmp_i != '\"'
			&& *exp->tmp_i != '\'')
			help_norm(exp, ms, last_token);
		if (ft_is_dollar(*exp->tmp_i) || *exp->tmp_i == '\"'
			|| *exp->tmp_i == '\'')
		{
			token->expanded = 1;
			token = last_token;
			return (NULL);
		}
		else
			return (last_token);
	}
	token = last_token;
	return (last_token);
}

void	shorten_exp(t_token *token, t_mini *ms, char *ptr)
{
	char	*tmp;

	tmp = ft_strjoin(token->str, ptr);
	free_and_null((void **)&token->str);
	free_expansion(tmp, ms->exp, ms);
	free_and_null((void **)&ptr);
	token->str = tmp;
}

t_token	*handle_expansion(t_token *token, t_expansion *exp, t_mini *ms)
{
	t_token	last_token;
	char *ptr;

	do_expand(exp->joker, exp, ms);
	if (exp->value != NULL)
	{
		if (exp->value[0] == '\0')
			token->ambiguous = true;
		ptr = ft_strtrim(exp->value, " ");
		if (!ptr)
			return (NULL);
		if (ft_strchr(ptr, ' ') == NULL)
			shorten_exp(token, ms, ptr);
		else
		{
			free_and_null((void **)&ptr);
			token = handle_splitting(exp, token, &last_token, ms);
			if (token)
			{
				token->expanded = 1;
				return (token);
			}
		}
	}
	else
		token->empty = true;
	return (NULL);
}
