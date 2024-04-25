/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/25 15:45:41 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*process_single_quotes(char *new, char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		new = add_char(new, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (new);
}

char	*process_double_quotes(char *new, char *str, int *i, t_mini *ms)
{
	while (str[*i] && str[*i] != '\"')
	{
		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i) + 1] != '$'
					&& str[(*i) + 1] != '\"' && str[(*i) + 1] != '?'
					&& ft_isalnum(str[(*i) + 1]))))
		{
			new = handle_dollar_sign(new, str, i, ms);
			if (!new)
				return (NULL);
		}
		replace_exit_code(str, &new, i, ms);
		if (ft_is_dollar(str[*i]))
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
	}
	if (str[*i] == '\"')
		(*i)++;
	return (new);
}

char	*expand_heredoc_delimeter(char *new, char *str, int *i, t_mini *ms)
{
	while (str[*i])
	{
		if (quote_check(str[*i], &ms->shell.quotes) != 0)
		{
			(*i)++;
			while (quote_check(str[*i], &ms->shell.quotes) != 0)
			{
				new = add_char(new, str[*i]);
				(*i)++;
			}
			(*i)++;
		}
		else
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
	}
	return (new);
}

void	expansion(t_token *token, t_mini *ms)
{
	t_expansion	exp;

	ms->exp = &exp;
	ft_bzero(&exp, sizeof(t_expansion));
	while (token != NULL)
	{
		if (token->str)
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
