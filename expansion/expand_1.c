/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/05/03 14:36:15 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	expand_init(t_expansion *exp, t_mini *ms, t_token *token)
{
	exp->joker = ft_strdup(token->str);
	free_and_null((void **)&token->str);
	free_expansion(exp->joker, ms->exp, ms);
	token->str = ft_strdup("");
	free_expansion(token->str, ms->exp, ms);
}

void	shift_tokens(t_token **token)
{
	while (token && (*token)->expanded == 1 && (*token)->next != NULL
		&& (*token)->next->expanded != 0)
		*token = (*token)->next;
}

t_token	*expand_variable(t_expansion *exp, t_token *token, t_mini *ms)
{
	t_token		*ret;

	expand_init(exp, ms, token);
	while (exp->joker[exp->i])
	{
		handle_heredoc_exp(token, exp, exp->joker, ms);
		replace_exit_code(exp->joker, &token->str, &exp->i, ms);
		quote_check(exp->joker[exp->i], &exp->quotes);
		if (exp->joker[exp->i] == S_QUOTE || exp->joker[exp->i] == D_QUOTE)
			handle_quotes(token, exp->joker, ms, exp);
		else if (exp->quotes == CLOSED)
		{
			ret = handle_closed(token, exp, ms);
			shift_tokens(&token);
			if (ret)
			{
				token->expanded = 1;
				free_and_null((void **)&exp->joker);
				return (ret);
			}
		}
	}
	free_and_null((void **)&exp->joker);
	return (token);
}

void	check_dol(t_token *token, t_expansion *exp, t_mini *ms)
{
	if (ft_is_dollar(exp->joker[exp->i]))
	{
		token->str = add_char(token->str, exp->joker[exp->i++]);
		free_expansion(token->str, ms->exp, ms);
	}
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
			free_expansion(token->str, exp, ms);
		}
		if (check_exp(exp->joker, exp->i))
		{
			ret = handle_expansion(token, exp, ms);
			shift_tokens(&token);
			if (ret)
				return (ret);
		}
		else if (exp->joker[exp->i] == '$' && exp->joker[exp->i + 1] == '?')
			replace_exit_code(exp->joker, &token->str, &exp->i, ms);
		else
			check_dol(token, exp, ms);
	}
	return (NULL);
}
