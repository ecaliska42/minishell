/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/25 12:35:48 by mesenyur         ###   ########.fr       */
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

t_token	*handle_splitting(t_expansion *exp, t_token *token, t_token **last_token, t_mini *ms)
{
	if (token->type != HEREDOC && token->type != RANDOM)
		token->ambiguous = true;
	exp->tmp_i = &exp->joker[exp->i];
	(*last_token) = split_value(exp->new_str, exp->value, token);
	free_expansion(last_token, ms->exp, ms);
	if (*exp->tmp_i)
	{
		while (*exp->tmp_i && *exp->tmp_i != '$' && *exp->tmp_i != '\"'
			&& *exp->tmp_i != '\'')
		{
			(*last_token)->str = add_char((*last_token)->str, *exp->tmp_i);
			free_expansion((*last_token)->str, ms->exp, ms);
			exp->i++;
			exp->tmp_i++;
		}
		exp->new_str = ft_strdup((*last_token)->str);
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
		{
			char	*tmp;
			tmp = ft_strjoin(exp->new_str, exp->value);
			free_and_null((void **)&exp->new_str);
			free_expansion(tmp, ms->exp, ms);
			free_and_null((void **)&exp->value);
			exp->new_str = tmp;
			// exp->new_str = ft_strjoin(exp->new_str, exp->value);
			// check_malloc_exit(exp->new_str, ms);
			// free_and_null((void **)&exp->value);
		}
		else
		{
			ret = handle_splitting(exp, token, &last_token, ms);
			// token = token->next;
			if (ret)
				return (ret);
		}
	}
	else
		token->empty = true;
	if (!exp->value)
		free_and_null((void **)&exp->tmp);
	return (NULL);
}

t_token	*handle_closed(t_token *token, t_expansion *exp, t_mini *ms)
{
	t_token	*ret;

	while (exp->joker[exp->i] && exp->joker[exp->i] != '\"'
		&& exp->joker[exp->i] != '\'')
	{
		while (exp->joker[exp->i] && exp->joker[exp->i] != '$'
			&& exp->joker[exp->i] != '\"' && exp->joker[exp->i] != '\'')
			exp->new_str = add_char(exp->new_str, exp->joker[exp->i++]);
		if (check_exp(exp->joker, exp->i))
		{
			ret = handle_expansion(token, exp, ms);
			if (ret)
			{
				free_and_null((void **)&exp->new_str);
				return (ret);
			}
			// token = token->next;
		}
		else if (replace_exit_code(exp->joker, &exp->new_str, &exp->i, ms))
			;
		else if (ft_is_dollar(exp->joker[exp->i]))
		{
			exp->new_str = add_char(exp->new_str, exp->joker[exp->i]);
			exp->i++;
		}
	}
	return (NULL);
}

t_token	*expand_variable(t_token *token, t_mini *ms)
{
	t_expansion	exp;
	t_token		*ret;
	
	ms->exp = &exp;
	ft_bzero(&exp, sizeof(t_expansion));
	exp.joker = ft_strdup(token->str);
	free_and_null((void **)&token->str);
	free_expansion(exp.joker, ms->exp, ms);
	exp.new_str = ft_strdup("");
	free_expansion(exp.new_str, ms->exp, ms);
	while (exp.joker[exp.i])
	{
		handle_heredoc_exp(token, &exp, exp.joker, ms);
		replace_exit_code(exp.joker, &exp.new_str, &exp.i, ms);
		quote_check(exp.joker[exp.i], &exp.quotes);
		if (exp.joker[exp.i] == S_QUOTE || exp.joker[exp.i] == D_QUOTE)
			handle_quotes(exp.joker, ms, &exp);
		else if (exp.quotes == CLOSED)
		{
			ret = handle_closed(token, &exp, ms);
			if (ret)
			{
				free_and_null((void **)&exp.new_str);
				return (ret);
			}
		}
	}
	token->str = exp.new_str;
	free_and_null((void **)&exp.joker);
	return (token);
}
