/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/28 11:15:53 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

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

t_token	*expand_variable(t_expansion exp, t_token *token, t_mini *ms)
{
	t_token		*ret;

	exp.joker = ft_strdup(token->str);
	free_and_null((void **)&token->str);
	free_expansion(exp.joker, ms->exp, ms);
	token->str = ft_strdup("");
	free_expansion(token->str, ms->exp, ms);
	while (exp.joker[exp.i])
	{
		handle_heredoc_exp(token, &exp, exp.joker, ms);
		replace_exit_code(exp.joker, &token->str, &exp.i, ms);
		quote_check(exp.joker[exp.i], &exp.quotes);
		if (exp.joker[exp.i] == S_QUOTE || exp.joker[exp.i] == D_QUOTE)
			handle_quotes(token, exp.joker, ms, &exp);
		else if (exp.quotes == CLOSED)
		{
			ret = handle_closed(token, &exp, ms);
			while (token && token->expanded == 1)
			{
				if (token->next == NULL || token->next->expanded == 0)
					break ;
				token = token->next;
			}
			if (ret)
			{
				free_and_null((void **)&exp.joker);
				return (ret);
			}
		}
	}
	free_and_null((void **)&exp.joker);
	return (token);
	
}

t_token	*handle_closed(t_token *token, t_expansion *exp, t_mini *ms)
{
	t_token	*ret;

	while (exp->joker[exp->i] && exp->joker[exp->i] != '\"'
		&& exp->joker[exp->i] != '\'')
	{
		while (exp->joker[exp->i] && exp->joker[exp->i] != '$'
			&& exp->joker[exp->i] != '\"' && exp->joker[exp->i] != '\'')
		{
			token->str = add_char(token->str, exp->joker[exp->i++]);
			free_expansion(token->str, ms->exp, ms);
		}			
		if (check_exp(exp->joker, exp->i))
		{
			ret = handle_expansion(token, exp, ms);
			while (token && token->expanded == 1)
			{
				if (token->next == NULL)
					break ;
				if (token->next->expanded == 0)
					break ;
				token = token->next;
			}
			if (ret)
				return (ret);
		}
		else if (exp->joker[exp->i] == '$' && exp->joker[exp->i + 1] == '?')
			replace_exit_code(exp->joker, &token->str, &exp->i, ms);
		else if (ft_is_dollar(exp->joker[exp->i]))
		{
			token->str = add_char(token->str, exp->joker[exp->i++]);
			free_expansion(token->str, ms->exp, ms);
		}
	}
	return (NULL);
}

void	handle_quotes(t_token * token, char *str, t_mini *ms, t_expansion *exp)
{
	if (str[exp->i] == S_QUOTE)
	{
		token->str = process_single_quotes(token->str, str, &exp->i);
		if (!token->str)
			free_expansion(NULL, ms->exp, ms);
		exp->quotes = CLOSED;
	}
	else if (exp->quotes == D_QUOTE)
	{
		exp->i++;
		token->str = process_double_quotes(token->str, str, &exp->i, ms);
		exp->quotes = CLOSED;
	}
}
