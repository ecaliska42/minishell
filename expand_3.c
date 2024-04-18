/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 19:50:45 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

t_token	*expand_variable(t_token *token, t_mini *ms, char quotes)
{
	char	*joker;
	char	*new;
	char	*value;
	char	*tmp_i;
	char	*tmp;
	int		len;
	int		i;
	t_token	*last_token;

	len = 0;
	i = 0;
	last_token = NULL;
	tmp = NULL;
	tmp_i = NULL;
	value = NULL;
	quotes = CLOSED;
	joker = token->str;
	new = ft_strdup("");
	while (joker[i])
	{
		if (token->type == HEREDOC)
		{
			token->flag_exp = true;
            while (joker[i++])
            {
                if (joker[i] == '\"' || joker[i] == '\'')
                    token->flag_exp = false;
            }
            i = 0;
			new = expand_heredoc_delimeter(new, joker, &i, ms);
		}
		replace_exit_code(joker, &new, &i, ms);
		quote_check(joker[i], &quotes);
		if (joker[i] == S_QUOTE)
		{
			new = process_single_quotes(new, joker, &i);
			quotes = CLOSED;
		}
		else if (quotes == D_QUOTE)
		{
            i++;
			new = process_double_quotes(new, joker, &i, ms);
			quotes = CLOSED;
		}
		else if (quotes == CLOSED)
		{
			while (joker[i] && joker[i] != '\"' && joker[i] != '\'')
			{
				while (joker[i] && joker[i] != '$' && joker[i] != '\"' && joker[i] != '\'')
					new = add_char(new, joker[i++]);
				if (ft_is_dollar(joker[i]) && (joker[i + 1] && joker[i + 1] != '$' && joker[i + 1] != '?' && joker[i + 1] != '/' && !ft_isdigit(joker[i + 1])))
				{
					i++;
					len = check_name_and_return_len(&joker[i]);
					tmp = ft_substr(joker, i, len);
					if (!tmp)
						return (NULL);
					i += len;
					if ((value = get_env_value(tmp, ms->env)) != NULL)
					{
						if (value[0] == '\0')
							token->ambiguous = true;
						value = ft_strtrim(value, " ");
						if (ft_strchr(value, ' ') == NULL)
						{
							new = ft_strjoin(new, value);
							free(value);
							continue ;
						}
						else
						{
							if (token->type != HEREDOC && token->type != RANDOM)
								token->ambiguous = true;
							tmp_i = &joker[i];
							last_token = split_value(new, value, token);
							if (*tmp_i)
							{
									while (*tmp_i && *tmp_i != '$' && *tmp_i != '\"' && *tmp_i != '\'')
									{
										last_token->str = add_char(last_token->str, *tmp_i);
										i++;
										tmp_i++;
									}
									new = ft_strdup(last_token->str);
									free(last_token->str);
									if (ft_is_dollar(*tmp_i) || *tmp_i == '\"' || *tmp_i == '\'')
									{
										token = last_token;
										continue ;
									}
									else
									{
										return (last_token);
									}
								if (ft_is_dollar(*tmp_i) || *tmp_i == '\"' || *tmp_i == '\'')
								{
									token = last_token;
									continue ;
								}
							}
							token = last_token;
							return (last_token);
						}
					}
					free (tmp);
				}
				else if (replace_exit_code(joker, &new, &i, ms));
				else if (ft_is_dollar(joker[i]))
				{
					new = add_char(new, joker[i]);
					i++;
				}
			}
		}
	}
	token->str = new;
	return (token);
}