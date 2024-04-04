/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/04 18:06:42 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"
#include "libraries/parsing.h"

char *replace_exit_code(char *str, int *i, t_env *envp)
{
	int exit_status;

	exit_status = envp->exit_status;
	if (str[*i] && str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '?')
	{
		(*i) += 2;
		return (ft_itoa(exit_status)); //protect
	}
	return (0);
}

char	*dollar_number(char *str, int *index, char *quotes)
{
	char *copy;
	int i;

	i = 0;
	// copy = ft_strdup("");
	copy = ft_calloc((ft_strlen(str) - *index) + 1, sizeof(char));	
	if (!copy)
		return (NULL);
	while (str[*index] && (str[*index] != '$' && !ft_is_space(str[*index])))
	{
		while (quote_check(str[*index], quotes) != CLOSED)
		{
			(*index)++;
			if (quote_check(str[*index], quotes) != CLOSED)
				copy[i++] = str[(*index)];
			else
				(*index)++;
		}
		copy[i++] = str[(*index)++];
	}
	copy[i] = '\0';
	return (copy);	
}

int	check_name_and_return_len(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (i);
		i++;
	}
	return (i); // not include dollar
}

char	*get_env_value(char *name, t_env *envp)
{
	while (envp)
	{
		if (ft_strcmp(name, envp->name) == 0)
			return (envp->values);
		envp = envp->next;
	}
	return (NULL);
}

char	*add_char(char *str, char new_char)
{
	char	*new;
	int		str_len;

	str_len = ft_strlen(str);
	new = ft_calloc(str_len + 2, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, str, str_len);
	new[str_len] = new_char;
	free(str);
	str = NULL;
	return (new);
}

t_token	*split_value(char *str, char *value, t_token *token, int flag)
{
	char	**words;
	t_token	*last;
	t_token	*new;
	int		i;

	i = 0;
	last = token;
	words = ft_split(value, ' ');
	if (words == NULL)
		return (NULL);
	if ((flag != 1 && flag != 3) && i == 0) // no space at start	 
	{
		last->str = ft_strjoin(str, words[0]);
		i++;
	}
	if ((flag == 1 || flag == 3) && (ft_strlen(str) == 0) && i == 0)  // if token is empty use the existing token 
	{
		last->str = ft_strjoin(str, words[0]);
		i++;
	}
	while (words[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		new->str = ft_strdup(words[i]);
		new->next = last->next;
		new->type = last->type;
		last->next = new;
		last = new;
		i++;
	}
	i = 0;
	while (words[i] != NULL)
	{
		free(words[i]);
		words[i] = NULL;
		i++;
	}
	free(words);
	words = NULL;
	return (last);
}

char	*process_single_quotes(char *new, char *str, int *i)
{
	(*i)++; // skip opening s_quote
	while (str[*i] && str[*i] != '\'')
	{
		new = add_char(new, str[*i]);
		(*i)++;
	}
	if (str[*i] == '\'')
		(*i)++; // skip closing s_quote
	return (new);
}

char	*process_double_quotes(char *new, char *str, int *i, t_env *envp)
{
	int		len;
	char	*tmp;
	char	*value;

	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i) + 1] != '$'
					&& str[(*i) + 1] != '\"' && str[(*i) + 1] != '?')))
		{
			(*i)++;
			len = check_name_and_return_len(&str[*i]);
			tmp = ft_substr(str, *i, len);
			if (!tmp)
				return (NULL);
			(*i) += len;
			if ((value = get_env_value(tmp, envp)) != NULL)
			{
				new = ft_strjoin(new, value);
			}
		}
		else if (str[*i] == '$' && str[(*i) + 1] == '?')
		{
			new = ft_strjoin(new ,replace_exit_code(str, i, envp));
		}
		else if (ft_is_dollar(str[*i]))
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

char	*expand_heredoc(char *new, char *str, int *i, t_env *envp)
{
	int		len;
	char	*tmp;
	char	*value;

	while (str[*i])
	{
		while (str[*i] && str[*i] != '$')
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i)
					+ 1] != '$')))
		{
			(*i)++;
			len = check_name_and_return_len(&str[*i]);
			tmp = ft_substr(str, *i, len);
			if (!tmp)
				return (NULL);
			(*i) += len;
			if ((value = get_env_value(tmp, envp)) != NULL)
			{
				new = ft_strjoin(new, value);
			}
		}
		while (str[*i] && str[*i] != '$' && str[*i])
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
	}
	return (new);
}

t_token	*expand_variable(t_token *token, t_env *envp, char quotes, int flag)
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
	flag = 0;
	last_token = NULL;
	tmp = NULL;
	tmp_i = NULL;
	value = NULL;
	quotes = CLOSED;
	joker = token->str;
	new = ft_strdup("");
	while (joker[i])
	{
		if (joker[i] == '$' && joker[i + 1] == '?')
		{
			// new = ft_strjoin(new, ft_itoa(envp->exit_status));
			// i += 2;
			new = ft_strjoin(new ,replace_exit_code(joker, &i, envp));
		}
		if (joker[i] == '$' && ft_isdigit(joker[i + 1]))
		{
			i += 2;
			new = ft_strjoin(new, dollar_number(joker, &i, &quotes));
		}
		quote_check(joker[i], &quotes);
		if (joker[i] == S_QUOTE)
		{
			new = process_single_quotes(new, joker, &i);
			quotes = CLOSED;
		}
		else if (quotes == D_QUOTE)
		{
			new = process_double_quotes(new, joker, &i, envp);
			quotes = CLOSED;
		}
		else if (quotes == CLOSED)
		{
			while (joker[i] && joker[i] != '\"' && joker[i] != '\'')
			{
				while (joker[i] && joker[i] != '$' && joker[i] != '\"' && joker[i] != '\'')
					new = add_char(new, joker[i++]);
				if (ft_is_dollar(joker[i]) && (joker[i + 1] && joker[i + 1] != '$' && joker[i + 1] != '?' && !ft_isdigit(joker[i + 1])))
				{
					i++;
					len = check_name_and_return_len(&joker[i]);
					tmp = ft_substr(joker, i, len);
					if (!tmp)
						return (NULL);
					i += len;
					if ((value = get_env_value(tmp, envp)) != NULL)
					{
						if (value[0] == '\0')
							token->ambiguous = true;
						value = skip_starting_ending_spaces(value);
						if (ft_strchr(value, ' ') == NULL) // single word value
						{
							new = ft_strjoin(new, value);
							continue ;
						}
						else
						{
							if (token->type != HEREDOC && token->type != RANDOM)
								token->ambiguous = true;
							tmp_i = &joker[i];
							last_token = split_value(new, value, token, flag);
							if (*tmp_i)
							{
									while (*tmp_i && *tmp_i != '$' && *tmp_i != '\"' && *tmp_i != '\'')
									{
										last_token->str = add_char(last_token->str, *tmp_i);
										i++;
										tmp_i++;
									}
									new = ft_strdup(last_token->str);
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
				}
				else if (joker[i] == '$' && joker[i + 1] == '?')
				{
					// new = ft_strjoin(new, ft_itoa(envp->exit_status));
					// i += 2;
					new = ft_strjoin(new ,replace_exit_code(joker, &i, envp));
				}
				if (joker[i] == '$' && ft_isdigit(joker[i + 1]))
				{
					i += 2;
					new = ft_strjoin(new, dollar_number(joker, &i, &quotes));
				}
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

void	expansion(t_token *token, t_env *envp, char quotes)
{
	quotes = CLOSED;
	while (token != NULL)
	{
		if (token->str)
		{
			// if (token->type != HEREDOC)
			// test if works for heredoc delimeter
			token = expand_variable(token, envp, CLOSED, 0);
		}
		if (token)
			token = token->next;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char	*skip_starting_ending_spaces(char *value)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	k = 0;
	i = 0;
	j = 0;
	while (value[i] && ft_is_space(value[i]))
		i++;
	while (value[j])
		j++;
	j--;
	while (j >= 0 && ft_is_space(value[j]))
		j--;
	new = malloc(j - i + 2);
	if (new == NULL)
		return (NULL);
	while (i <= j)
	{
		new[k] = value[i];
		i++;
		k++;
	}
	new[k] = '\0';
	// free(value);
	// value = NULL;
	return (new);
}


