/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/17 11:52:52 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"

int	check_name_and_return_len(char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (false);
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*get_env_value(char *name, t_env *envp, int len)
{
	(void)len;
	while (envp)
	{
		if (ft_strcmp(name, envp->name) == 0)
			return (envp->values); //
		envp = envp->next;
	}
	return (NULL);
}

void	ft_skip_dollar(char **name)
{
	(*name)++;
	while (**name == '$')
		(*name)++;
}

char	*str_replace(char *str, char *name, char *value)
{
	int		len;
	char	*pos;
	char	*new_str;
	int		name_len;

	name_len = ft_strlen(name);
	pos = ft_strnstr(str, name, name_len);
	if (pos != NULL)
	{
		len = ft_strlen(str) - check_name_and_return_len(name)
			+ ft_strlen(value) + 1;
		new_str = (char *)malloc(len * sizeof(char));
		if (new_str == NULL)
			return (NULL);
		ft_strlcpy(new_str, str, len);
		new_str[pos - str] = '\0'; // + 1);
		ft_strlcat(new_str, value, len);
		ft_strlcat(new_str, pos + name_len, len);
		return (new_str);
	}
	return (str);
}

t_token	*split_value(char *value, t_token *token)
{
	char	**words;
	t_token	*last;
	t_token	*new;
	int		i;

	i = 0;
	last = token;
	words = ft_split(value, ' ');
	while (words[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		new->str = words[i];
		new->next = NULL;
		new->type = 5;
		last->next = new;
		last = new;
		i++;
	}
	free(words);
	return (last); // return last token of the new tokens created from value
}

void	replace_variable_in_token(t_token *token, char *name)
{
	char	*new;

	new = str_replace(token->str, name, "");
	if (new == NULL)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
	else
	{
		free(token->str);
		token->str = new;
	}
}

t_token	*expand_token(t_token *token, t_env *envp)
{
	t_token	*last_token;
	char	*name;
	char	*value;
	int		len;
	char 	*new;
	char	*tmp;

	name = token->str;
	tmp = name; //  original value of name
	while ((name = ft_strchr(name, '$')) != NULL)
	{
		// tmp = ft_substr(tmp, 0, name - tmp);
		// printf("=========================================\n");
		// printf("tmp: %s\n", tmp);
		// printf("=========================================\n");
		ft_skip_dollar(&name);
		len = check_name_and_return_len(name); // len is var_name len
		if ((*name) && len > 0)
		{
			if ((value = get_env_value(name, envp, len)) != NULL)
			{
				last_token = split_value(value, token);
				last_token->type = 5;
				replace_variable_in_token(token, name);
			}
			else
			{
				new = str_replace(token->str, name, "");
				if (new == NULL)
				{
					ft_putstr_fd("Error: malloc failed\n", 2);
					exit(1);
				}
				else
				{
					free(token->str);
					token->str = new;
				}
			}
			name += len ;
		}
	}
	return (token);
}

void	expand_variable(t_token *token, t_env *envp)
{
	while (token != NULL)
	{
		token = expand_token(token, envp);
		token = token->next;
	}
}

void	remove_quotes(t_token *token)
{
	int		i;
	char	*str;
	char		quote;

	i = 0;
	quote = CLOSED;
	str = token->str;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote_check(str[i], &quote);
			//remove quote and skip to next char
			while (quote_check(str[i], &quote) != 0)
			{
				// skip while quote is open
			}
			// remove quote and check if word continues
		}
		i++;
	}
	token = token->next;
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