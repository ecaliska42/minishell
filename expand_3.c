/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/19 17:57:13 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"

int do_expand(char *str, t_expansion *exp, t_mini *ms)
{
	exp->i++;
	exp->len = check_name_and_return_len(&str[exp->i]);
	exp->tmp = ft_substr(str, exp->i, exp->len);
	if (!exp->tmp)
		return (-1);
	exp->i += exp->len;
	exp->value = get_env_value(exp->tmp, ms->env);
	return (0);
}

bool check_exp(char *str, int i)
{
	if (ft_is_dollar(str[i]) && (str[i + 1] && str[i + 1] != '$'
		&& str[i + 1] != '?' && str[i + 1] != '/'))
		return (true);
	return (false);
}

void handle_quotes(char *str, t_mini *ms, t_expansion *exp)
{
	if (str[exp->i] == S_QUOTE)
	{
		exp->new_str = process_single_quotes(exp->new_str, str, &exp->i);
		exp->quotes = CLOSED;
	}
	else if (exp->quotes == D_QUOTE)
	{
		exp->i++;
		exp->new_str = process_double_quotes(exp->new_str, str, &exp->i, ms);
		exp->quotes = CLOSED;
	}
}

int handle_heredoc_exp(t_token *token, t_expansion *exp, char *str, t_mini *ms)
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

void handle_closed_quotes(char *joker, t_expansion *exp, t_mini *ms, t_token **token, t_token **last_token)
{
    while (joker[exp->i] && joker[exp->i] != '\"' && joker[exp->i] != '\'')
    {
        while (joker[exp->i] && joker[exp->i] != '$' && joker[exp->i] != '\"' && joker[exp->i] != '\'')
            exp->new_str = add_char(exp->new_str, joker[exp->i++]);
        if (check_exp(joker, exp->i))
        {
            do_expand(joker, exp, ms);
            if (exp->value != NULL)
            {
                if (exp->value[0] == '\0')
                    (*token)->ambiguous = true;
                exp->value = ft_strtrim(exp->value, " ");
                if (ft_strchr(exp->value, ' ') == NULL)
                {
                    exp->new_str = ft_strjoin(exp->new_str, exp->value);
                    free(exp->value);
                }
                else
                {
                    if ((*token)->type != HEREDOC && (*token)->type != RANDOM)
                        (*token)->ambiguous = true;
                    exp->tmp_i = &joker[exp->i];
                    *last_token = split_value(exp->new_str, exp->value, *token);
                    if (*exp->tmp_i)
                    {
                        char *value_ptr = exp->value;
                        while (*value_ptr && *value_ptr != '$' && *value_ptr != '\"' && *value_ptr != '\'') 
                        {
                            (*last_token)->str = add_char((*last_token)->str, *value_ptr);
                            value_ptr++;
                        }
                        exp->new_str = ft_strdup((*last_token)->str);
                        if (ft_is_dollar(*value_ptr) || *value_ptr == '\"' || *value_ptr == '\'') 
                            *token = *last_token;
                        else
                        {
                            *token = *last_token;
                            return;
                        }
                    }
                    *token = *last_token;
                    return;
                }
            }
            free(exp->tmp);
        }
        else if (replace_exit_code(joker, &exp->new_str, &exp->i, ms));
        else if (ft_is_dollar(joker[exp->i]))
        {
            exp->new_str = add_char(exp->new_str, joker[exp->i]);
            exp->i++;
        }
    }
}

t_token	*expand_variable(t_token *token, t_mini *ms)
{
	char	*joker;
	t_expansion	exp;
	t_token	*last_token;

	last_token = NULL;
	joker = token->str;
	ft_bzero(&exp, sizeof(t_expansion));
	exp.new_str = ft_strdup("");
	while (joker[exp.i])
	{
		handle_heredoc_exp(token, &exp, joker, ms);
		replace_exit_code(joker, &exp.new_str, &exp.i, ms);
		quote_check(joker[exp.i], &exp.quotes);
		if (joker[exp.i] == S_QUOTE || joker[exp.i] == D_QUOTE)
			handle_quotes(joker, ms, &exp);
		else if (exp.quotes == CLOSED)
		{
			while (joker[exp.i] && joker[exp.i] != '\"' && joker[exp.i] != '\'')
			{
				while (joker[exp.i] && joker[exp.i] != '$' && joker[exp.i] != '\"' && joker[exp.i] != '\'')
					exp.new_str = add_char(exp.new_str, joker[exp.i++]);
				if (check_exp(joker, exp.i))
				{
					do_expand(joker, &exp, ms);
					if (exp.value != NULL)
					{
						if (exp.value[0] == '\0')
							token->ambiguous = true;
						exp.value = ft_strtrim(exp.value, " ");
						if (ft_strchr(exp.value, ' ') == NULL)
						{
							exp.new_str = ft_strjoin(exp.new_str, exp.value);
							free(exp.value);
							continue ;
						}
						else
						{
							if (token->type != HEREDOC && token->type != RANDOM)
								token->ambiguous = true;
							exp.tmp_i = &joker[exp.i];
							last_token = split_value(exp.new_str, exp.value, token);
							if (*exp.tmp_i)
							{
								while (*exp.tmp_i && *exp.tmp_i != '$' && *exp.tmp_i != '\"' && *exp.tmp_i != '\'')
								{
									last_token->str = add_char(last_token->str, *exp.tmp_i);
									exp.i++;
									exp.tmp_i++;
								}
								exp.new_str = ft_strdup(last_token->str);
								if (ft_is_dollar(*exp.tmp_i) || *exp.tmp_i == '\"' || *exp.tmp_i == '\'')
								{
									token = last_token;
									continue ;
								}
								else
									return (last_token);
								if (ft_is_dollar(*exp.tmp_i) || *exp.tmp_i == '\"' || *exp.tmp_i == '\'')
								{
									token = last_token;
									continue ;
								}
							}
							token = last_token;
							return (last_token);
						}
					}
					free (exp.tmp);
				}
				else if (replace_exit_code(joker, &exp.new_str, &exp.i, ms));
				else if (ft_is_dollar(joker[exp.i]))
				{
					exp.new_str = add_char(exp.new_str, joker[exp.i]);
					exp.i++;
				}
			}
		}
	}
	token->str = exp.new_str;
	return (token);
}
