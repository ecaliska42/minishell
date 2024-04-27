/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/27 11:29:47 by mesenyur         ###   ########.fr       */
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
				free_expansion(NULL, ms->exp, ms);
		}
		replace_exit_code(str, &new, i, ms);
		if (ft_is_dollar(str[*i]))
		{
			new = add_char(new, str[*i]);
			if (!new)
				free_expansion(NULL, ms->exp, ms);
			(*i)++;
		}
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		{
			new = add_char(new, str[*i]);
			if (!new)
				free_expansion(NULL, ms->exp, ms);
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

// void free_all_t_tokens(t_token *token)
// {
// 	t_token	*tmp;

// 	while (token)
// 	{
// 		tmp = token->next;
// 		free_and_null((void **)&token->str);
// 		free_and_null((void **)&token);
// 		token = tmp;
// 	}
// }

void	expansion(t_token *token, t_mini *ms)
{
	t_expansion	exp;

	ms->exp = &exp;
	ft_bzero(&exp, sizeof(t_expansion));
	while (token != NULL)
	{
		if (token->str && token->expanded == 0)
		{

			token = expand_variable(exp, token, ms);
		}
		if (token)
			token = token->next;
	}
	// free_all_t_tokens(token);
}

t_token	*expand_variable(t_expansion exp, t_token *token, t_mini *ms)
{
	t_token		*ret;

	exp.joker = ft_strdup(token->str);
	free_and_null((void **)&token->str);
	free_expansion(exp.joker, ms->exp, ms);
	token->str = ft_strdup("");
	// token->expanded = 0;
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
				token->token_count = exp.word_count;
				free_and_null((void **)&exp.joker);
				return (ret);
			}
		}
	}
	
	free_and_null((void **)&exp.joker);
	return (token);
}
