/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:01:15 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 13:24:03 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	do_expand(char *str, t_expansion *exp, t_mini *ms, t_token *token)
{
	int	i;

	i = 0;
	exp->i++;
	exp->len = check_name_and_return_len(&str[exp->i]);
	exp->tmp = ft_substr(str, exp->i, exp->len);
	if (!exp->tmp)
		return (-1);
	exp->i += exp->len;
	exp->value = get_env_value(exp->tmp, ms->env);
	free_and_null((void **)&exp->tmp);
	if (exp->value)
	{
		while (ft_is_white_space(exp->value[i]))
		{
			i++;
			if (exp->value[i] == '\0')
				token->ambiguous = true;
		}
	}
	return (0);
}

bool	check_exp(char *str, int i)
{
	if (ft_is_dollar(str[i]) && (str[i + 1] && str[i + 1] != '$' && str[i
				+ 1] != '?' && str[i + 1] != '/'))
		return (true);
	return (false);
}

char	*process_single_quotes(char *new, char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		new = add_char(new, str[*i]);
		if (!new)
			return (NULL);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (new);
}

static void	helper(char **new, char *str, int **i, t_mini *ms)
{
	if (ft_is_dollar(str[**i]) && !ft_isalnum(str[(**i) + 1]))
	{
		*new = add_char(*new, str[**i]);
		free_expansion(new, ms->exp, ms);
		(**i)++;
	}
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
			free_expansion(new, ms->exp, ms);
		}
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		{
			new = add_char(new, str[*i]);
			free_expansion(new, ms->exp, ms);
			(*i)++;
		}
		replace_exit_code(str, &new, i, ms);
		helper(&new, str, &i, ms);
	}
	if (str[*i] == '\"')
		(*i)++;
	return (new);
}
