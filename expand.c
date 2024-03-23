/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/24 00:55:23 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"

int check_name_and_return_len(char *name)
{
	int i;

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

char *add_char(char *str, char new_char)
{
	
	char	*new;
	int 	str_len;

	str_len = ft_strlen(str);
	new = ft_calloc(str_len + 2, sizeof(char));
	if (new == NULL)
		return(NULL);
	ft_memcpy(new, str, str_len);
	new[str_len] = new_char;
	free(str);
	return (new);
}

t_token *split_value(char *str, char *value, t_token *token, int flag)
{
	char **words;
	t_token *last;
	t_token *new;
	int i;
	
	i = 0;
	last = token;
	words = ft_split(value, ' ');
	if (words == NULL)
		return (NULL);
	if (flag != 1 && flag != 3)
	{
		last->str = ft_strjoin(str, words[0]);
		i++;
	}
	while (words[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		new->str = words[i];
		new->next = NULL;
		new->type = token->type;
		last->next = new;
		last = new;
		i++;
	}
	free(words);
	return (last);
}

char *process_single_quotes(char *new, char *str, int *i)
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

char *process_double_quotes(char *new, char *str, int *i, t_env *envp) // works
{
	int	len;
	char *tmp;
	char *value;
	
	(*i)++;
	while(str[*i] && str[*i] != '\"')
	{
		
		while (str[*i] && str[*i] != '$' && str[*i] != '\"')
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i) + 1] != '$')))
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

char *expand_heredoc(char *new, char *str, int *i, t_env *envp)
{
	int	len;
	char *tmp;
	char *value;
	
	while (str[*i])
	{
		while (str[*i] && str[*i] != '$')
		{
			new = add_char(new, str[*i]);
			(*i)++;
		}
		if ((ft_is_dollar(str[*i])) && (str[(*i) + 1] && (str[(*i) + 1] != '$')))
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

// char *process_no_quotes(char *new, char *str, int *i, t_env *envp)
// {
// 	t_token *token;
// 	char *tmp;
// 	char *value;
// 	int len;

// 	while (str[*i] && str[*i] != '$' && str[*i] != '\"' && str[*i] != '\'')
// 	{
// 		new = add_char(new, str[(*i)++]);	
// 	}
// 	if (ft_is_dollar(str[*i]) && (str[(*i) + 1] && str[(*i) + 1] != '$'))
// 	{
// 		(*i)++;
// 		len = check_name_and_return_len(&str[*i]);
// 		tmp = ft_substr(str, *i, len);
// 		if (!tmp)
// 			return (NULL);
// 		(*i) += len;
// 		if ((value = get_env_value(tmp, envp)) != NULL)
// 		{
// 			if (split_value(value, token) == 2) // space at end
// 			{
// 				printf("value[0]: %c\n", value[0]);
// 				printf("value[last ]: %c\n", value[ft_strlen(value) - 1]);
// 			}
			// while (token->str[i] && token->str[i] != '$' && token->str[i] != '\"' && token->str[i] != '\'')
			// {
			// 	token->str = add_char(token->str, token->str[i]);
			// 	i++;
			// }
// 		}
// 	}

t_token *expand_variable(t_token *token, t_env *envp, char quotes, int flag)
{
	char 	*new;
	char	*value;
	int		len;
	int 	i;
	char	*tmp;
	t_token *last_token;
	char *tmp_token;

	flag = 0;
	tmp = NULL;
	last_token = NULL;
	tmp_token = NULL;
	len = 0;
	value = NULL;
	i = 0;
	quotes = CLOSED;
	new = ft_strdup("");
	while (token->str[i])
	{
		quote_check(token->str[i], &quotes);
		if (token->str[i] == S_QUOTE)
		{
			new = process_single_quotes(new, token->str, &i);
			quotes = CLOSED;
		}
		else if (quotes == D_QUOTE)
		{
			new = process_double_quotes(new, token->str, &i, envp);
			quotes = CLOSED;
		}
		else if (quotes == CLOSED)
		{
			while (token->str[i] && token->str[i] != '$' && token->str[i] != '\"' && token->str[i] != '\'')
					new = add_char(new, token->str[i++]);
			if (ft_is_dollar(token->str[i]) && (token->str[i + 1] && token->str[i + 1] != '$'))
			{
				i++;
				len = check_name_and_return_len(&token->str[i]);
				tmp = ft_substr(token->str, i, len);
				if (!tmp)
					return (NULL);
				i += len;
				if ((value = get_env_value(tmp, envp)) != NULL)
				{
					if (value[0] == ' ')
					{
						flag = 1; 					// space at start
						if (value[ft_strlen(value) - 1] == ' ') 
							flag = 3; 				// space at start and end
					}
					else if (value[ft_strlen(value) - 1] == ' ')
						flag = 2; 			// space at end
					
					if (ft_strchr(value, ' ') == NULL) // single word value
					{
						new = ft_strjoin(new, value);
						continue ;
					}	
					else 
					{
						// value = skip_starting_ending_spaces(value);
						tmp_token = &token->str[i];
						token = split_value(new, value, token, flag);
						if (tmp_token[i] && flag != 2 && flag != 3) // if has NO space at end
						{
							while (tmp_token[i] && tmp_token[i] != '$' && tmp_token[i] != '\"' && tmp_token[i] != '\'')
							{	
								token->str = add_char(token->str, tmp_token[i]);
								i++;
							}						
						}	
						else
							return (token);
					}
				}
			}
			else if (ft_is_dollar(token->str[i]))
			{
				new = add_char(new, token->str[i]);
				i++;
			}
		}
	}
	free(token->str);
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
			// if (token->type != HEREDOC) // test if works for heredoc delimeter
			token = expand_variable(token, envp, CLOSED, 0);
		}
		if (token)
			token = token->next;
	}
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *skip_starting_ending_spaces(char *value)
{
	int i;
	int j;
	int k;
	char *new;

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
	free(value);
	return (new);
}