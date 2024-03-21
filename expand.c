/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:20:55 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/21 18:39:42 by mesenyur         ###   ########.fr       */
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

// char *str_replace(char *str, char *name, char *value)
// {
// 	int		len;
//     char	*pos;
// 	char	*new_str;
// 	int		name_len;

// 	name_len = ft_strlen(name);
// 	pos = ft_strnstr(str, name, name_len);
//     if (pos != NULL)
// 	{
//         len = ft_strlen(str) + ft_strlen(value) - ft_strlen(name) + 1;
//         new_str = malloc(len);
//         if (new_str == NULL)
//             return NULL;
// 		ft_strlcpy(new_str, str, pos - str + 1);
//         new_str[pos - str] = '\0';
// 		ft_strlcat(new_str, value, len);
// 		ft_strlcat(new_str, pos + name_len, len);
//         return (new_str);
//     }
//     return (str);
// }

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

int	split_value(char *value, t_token *token)
{
	char **words;
	t_token *last;
	t_token *new;
	int i;
	int flag;

	i = 0;
	flag = 0;
	// if (ft_is_space(value[0]) && ft_is_space(value[ft_strlen(value) - 1]))
	// 	flag = 2; // space at start and end
	if (ft_is_space(value[0])) 
	{
		flag = 1; // space at start
		if (ft_is_space(value[ft_strlen(value) - 1]))
			flag = 3; // space at start and end
	}
	else if (ft_is_space(value[ft_strlen(value) - 1]))
		flag = 2;
	// else if (!ft_is_space(value[0]) && ft_is_space(value[ft_strlen(value) - 1]))
	// 	flag = 3; // space at end
	// else
	// 	flag = 0; // no space at start and end
	// value = skip_starting_ending_spaces(value);
	last = token;
	// printf("last->str: %s\n", last->str);
	words = ft_split(value, ' ');
	if (words == NULL)
		return (-1);
	if (flag != 1)
	{
		last->str = ft_strjoin(last->str, words[0]);
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
	return (flag);
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

void expand_variable(t_token *token, t_env *envp, char quotes)
{
	char 	*new;
	char	*value;
	int		len;
	int 	i;
	// t_token *last_token;
	char *tmp;

	tmp = NULL;
	// last_token = token;
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
			i++;
			while (token->str[i] && token->str[i] != '$' && token->str[i] != '\"')
					new = add_char(new, token->str[i++]);
			if (ft_is_dollar(token->str[i]) && (token->str[i + 1] && token->str[i + 1] != '$'))
			{
				i++;
				len = check_name_and_return_len(&token->str[i]);
				tmp = ft_substr(token->str, i, len);
				if (!tmp)
					return ;
				i += len;
				if ((value = get_env_value(tmp, envp)) != NULL)
				{
					new = ft_strjoin(new, value);
				}
			}
			while (token->str[i] && token->str[i] != '$' && token->str[i] != '\"')
					new = add_char(new, token->str[i++]);
			if (token->str[i] == '\"')
			{
				quotes = CLOSED;
				i++;
			}
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
					return ;
				i += len;
				if ((value = get_env_value(tmp, envp)) != NULL)
				{
					// new = ft_strjoin(new, value);
					if (split_value(value, token) == 2)
						break ;	
					// i += len;
				}
			}
		}
	}
	free(token->str);
	token->str = new;
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


// 					new = str_replace(token->str, name, value);
// 					free(token->str);
// 					token->str = new;
// 					i += len;
// 
//     				printf("git checkout expansion");

void	expansion(t_token *token, t_env *envp, char quotes)
{
	// int i;

	// i = 0;
	quotes = CLOSED;
	while (token != NULL)
	{
		if (token->str)
			expand_variable(token, envp, CLOSED);
		// if (ft_strchr(token->str, '$') != NULL)
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
