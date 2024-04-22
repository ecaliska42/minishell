/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:01:35 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/22 13:54:44 by mesenyur         ###   ########.fr       */
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

t_token *handle_closed_quotes(t_token *token, char *str, t_expansion *exp,  t_mini *ms)
{
	t_token	*last_token;

	last_token = NULL;
	while (str[exp->i] && str[exp->i] != '\"' && str[exp->i] != '\'')
			{
				while (str[exp->i] && str[exp->i] != '$' && str[exp->i] != '\"' && str[exp->i] != '\'')
					exp->new_str = add_char(exp->new_str, str[exp->i++]);
				if (check_exp(str, exp->i))
				{
					do_expand(str, exp, ms);
					if (exp->value != NULL)
					{
						if (exp->value[0] == '\0')
							token->ambiguous = true;
						exp->value = ft_strtrim(exp->value, " ");
						if (ft_strchr(exp->value, ' ') == NULL)
						{
							exp->new_str = ft_strjoin(exp->new_str, exp->value);
							free(exp->value);
							continue ;
						}
						else
						{
							if (token->type != HEREDOC && token->type != RANDOM)
								token->ambiguous = true;
							exp->tmp_i = &str[exp->i];
							last_token = split_value(exp->new_str, exp->value, token);
							if (*exp->tmp_i)
							{
									while (*exp->tmp_i && *exp->tmp_i != '$' && *exp->tmp_i != '\"' && *exp->tmp_i != '\'')
									{
										last_token->str = add_char(last_token->str, *exp->tmp_i);
										exp->i++;
										exp->tmp_i++;
									}
									exp->new_str = ft_strdup(last_token->str);
									if (ft_is_dollar(*exp->tmp_i) || *exp->tmp_i == '\"' || *exp->tmp_i == '\'')
									{
										token = last_token;
										continue ;
									}
									else
										return (last_token);
								if (ft_is_dollar(*exp->tmp_i) || *exp->tmp_i == '\"' || *exp->tmp_i == '\'')
								{
									token = last_token;
									continue ;
								}
							}
							token = last_token;
							return (last_token);
						}
					}
					free (exp->tmp);
				}
				else if (replace_exit_code(str, &exp->new_str, &exp->i, ms));
				else if (ft_is_dollar(str[exp->i]))
				{
					exp->new_str = add_char(exp->new_str, str[exp->i]);
					exp->i++;
				}
			}
	return (token);
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

// t_token	*expand_variable(t_token *token, t_mini *ms, char quotes)
// {
// 	int 	i;
// 	char	*joker;
// 	t_token	*last_token;
// 	char	*new;
// 	char	*tmp;
// 	char	*value;
// 	char	*tmp_i;
// 	int		len;

// 	len = 0;
// 	i = 0;
// 	last_token = NULL;
// 	tmp = NULL;
// 	tmp_i = NULL;
// 	value = NULL;
// 	quotes = CLOSED;
// 	joker = token->str;
// 	new = ft_strdup("");
// 	while (joker[i])
// 	{
// 		if (token->type == HEREDOC)
// 		{
// 			token->flag_exp = true;
//             while (joker[i++])
//             {
//                 if (joker[i] == '\"' || joker[i] == '\'')
//                     token->flag_exp = false;
//             }
//             i = 0;
// 			new = expand_heredoc_delimeter(new, joker, &i, ms);
// 		}
// 		replace_exit_code(joker, &new, &i, ms);
// 		quote_check(joker[i], &quotes);
// 		if (joker[i] == S_QUOTE)
// 		{
// 			new = process_single_quotes(new, joker, &i);
// 			quotes = CLOSED;
// 		}
// 		else if (quotes == D_QUOTE)
// 		{
//             i++;
// 			new = process_double_quotes(new, joker, &i, ms);
// 			quotes = CLOSED;
// 		}
// 		else if (quotes == CLOSED)
// 		{
// 			while (joker[i] && joker[i] != '\"' && joker[i] != '\'')
// 			{
// 				while (joker[i] && joker[i] != '$' && joker[i] != '\"' && joker[i] != '\'')
// 					new = add_char(new, joker[i++]);
// 				if (ft_is_dollar(joker[i]) && (joker[i + 1] && joker[i + 1] != '$' && joker[i + 1] != '?' && joker[i + 1] != '/' && !ft_isdigit(joker[i + 1])))
// 				{
// 					i++;
// 					len = check_name_and_return_len(&joker[i]);
// 					tmp = ft_substr(joker, i, len);
// 					if (!tmp)
// 						return (NULL);
// 					i += len;
// 					if ((value = get_env_value(tmp, ms->env)) != NULL)
// 					{
// 						if (value[0] == '\0')
// 							token->ambiguous = true;
// 						value = ft_strtrim(value, " ");
// 						if (ft_strchr(value, ' ') == NULL)
// 						{
// 							new = ft_strjoin(new, value);
// 							free(value);
// 							continue ;
// 						}
// 						else
// 						{
// 							if (token->type != HEREDOC && token->type != RANDOM)
// 								token->ambiguous = true;
// 							tmp_i = &joker[i];
// 							last_token = split_value(new, value, token);
// 							if (*tmp_i)
// 							{
// 									while (*tmp_i && *tmp_i != '$' && *tmp_i != '\"' && *tmp_i != '\'')
// 									{
// 										last_token->str = add_char(last_token->str, *tmp_i);
// 										i++;
// 										tmp_i++;
// 									}
// 									new = ft_strdup(last_token->str);
									
// 									if (ft_is_dollar(*tmp_i) || *tmp_i == '\"' || *tmp_i == '\'')
// 									{
// 										token = last_token;
// 										continue ;
// 									}
// 									else
// 									{
// 										return (last_token);
// 									}
// 								if (ft_is_dollar(*tmp_i) || *tmp_i == '\"' || *tmp_i == '\'')
// 								{
// 									token = last_token;
// 									continue ;
// 								}
// 							}
// 							token = last_token;
// 							return (last_token);
// 						}
// 					}
// 					free (tmp);
// 				}
// 				else if (replace_exit_code(joker, &new, &i, ms));
// 				else if (ft_is_dollar(joker[i]))
// 				{
// 					new = add_char(new, joker[i]);
// 					i++;
// 				}
// 			}
// 		}
// 	}
// 	token->str = new;
// 	return (token);
// }
