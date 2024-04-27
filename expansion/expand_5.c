/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:01:15 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/27 11:30:20 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	do_expand(char *str, t_expansion *exp, t_mini *ms)
{
	exp->i++;
	exp->len = check_name_and_return_len(&str[exp->i]);
	exp->tmp = ft_substr(str, exp->i, exp->len);
	if (!exp->tmp)
		return (-1);
	exp->i += exp->len;
	exp->value = get_env_value(exp->tmp, ms->env);
	free_and_null((void **)&exp->tmp);
	return (0);
}

bool	check_exp(char *str, int i)
{
	if (ft_is_dollar(str[i]) && (str[i + 1] && str[i + 1] != '$'
			&& str[i + 1] != '?' && str[i + 1] != '/'))
		return (true);
	return (false);
}

void	handle_quotes(t_token * token, char *str, t_mini *ms, t_expansion *exp)
{
	if (str[exp->i] == S_QUOTE)
	{
		token->str = process_single_quotes(token->str, str, &exp->i);
		exp->quotes = CLOSED;
	}
	else if (exp->quotes == D_QUOTE)
	{
		exp->i++;
		token->str = process_double_quotes(token->str, str, &exp->i, ms);
		exp->quotes = CLOSED;
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
			token->str = add_char(token->str, exp->joker[exp->i++]);
		if (check_exp(exp->joker, exp->i))
		{
			ret = handle_expansion(token, exp, ms);
			while (token && token->expanded == 1)
			{
				if (token->next == NULL)
					break ;
				token = token->next;
			}
			if (ret)
				return (ret);
		}
		else if (exp->joker[exp->i] == '$' && exp->joker[exp->i + 1] == '?')
			replace_exit_code(exp->joker, &token->str, &exp->i, ms);
		else if (ft_is_dollar(exp->joker[exp->i]))
			token->str = add_char(token->str, exp->joker[exp->i++]);
	}
	return (NULL);
}
