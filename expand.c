/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/28 20:43:11 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"
#include "libraries/parsing.h"

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
	if ((flag != 1 && flag != 3) && i == 0) // if has NO space at start
	{
		// printf("str: %s\n", str);
		last->str = ft_strjoin(str, words[0]);
		// printf("last->str: %s\n", last->str);
		i++;
	}
	if ((flag == 1 || flag == 3) && (ft_strlen(str) == 0) && i == 0)
	// str is empty so use new instead new token
	{
		last->str = ft_strjoin(str, words[0]);
		i++;
	}
	// if ((flag == 1 || flag == 3) && i == 0)
	// {
	// 	new = malloc(sizeof(t_token));
	// 	new->str = ft_strdup(words[i]);
	// 	new->next = token->next;
	// 	new->type = token->type;
	// 	last->next = new;
	// 	last = new;
	// 	i++;
	// }
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
		i++;
	}
	free(words);
	return (last);
}

// void split_value(char *str, t_token *token)//, int flag)
// {
// 	char **words;
// 	t_token *last;
// 	t_token *new;
// 	int i;

// 	i = 0;
// 	last = token;
// 	words = ft_split(str, ' ');
// 	if (words == NULL)
// 		return ;
// 	while (words[i] != NULL)
// 	{
// 		new = malloc(sizeof(t_token));
// 		new->str = ft_strdup(words[i]);
// 		new->next = NULL;
// 		new->type = token->type;
// 		last->next = new;
// 		last = new;
// 		i++;
// 	}
// 	i = 0;
// 	while (words[i] != NULL)
// 	{
// 		free(words[i]);
// 		i++;
// 	}
// 	free(words);
// }

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
					&& str[(*i) + 1] != '\"')))
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
				if (ft_is_dollar(joker[i]) && (joker[i + 1] && joker[i + 1] != '$'))
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
						if (value[0] == ' ')
						{
							flag = 1; // space at start
							if (value[ft_strlen(value) - 1] == ' ')
								flag = 3; // space at start and end
						}
						else if (value[ft_strlen(value) - 1] == ' ')
							flag = 2;                      // space at end
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
							// if (flag == 2 || flag == 3)
							// {
							// }
							if (*tmp_i)
							{
								// if (*tmp_i && flag != 2 && flag != 3)
								// // if has NO space at end
								// {
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
										printf("else str: %s\n", token->str);
										return (last_token);
									}
								// }
								if (ft_is_dollar(*tmp_i) || *tmp_i == '\"' || *tmp_i == '\'')
								{
									token = last_token;
									continue ;
								}
							}
							token = last_token;
							return (token);
						}
					}
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
