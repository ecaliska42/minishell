/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/25 13:18:58 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*process_single_quotes(char *new, char *str, int *i)
{
	// char *tmp;
	
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

// char *shorten(char *new, int **i, char *str)
// {
// 	char *tmp;
// 	tmp = add_char(new, str[**i]);
// 	// free_and_null((void **)new);
// 	new = tmp;
// 	(**i)++;
// 	return (new);
// }

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
	while (token != NULL)
	{
		if (token->str)
			token = expand_variable(token, ms);
		if (token)
			token = token->next;
	}
}
