/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/15 00:04:05 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"

bool env_exists(char *name, t_env *envp, int len)
{
	while (envp)
	{
		if (ft_strncmp(name, envp->name, len) == 0)
			return (true);
		envp = envp->next;
	}
	return (false);
}

int check_name_and_return_len(char *name)
{
	int i;

	i = 0;
	if (!name)
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (i);
}

char *get_env_value(char *name, t_env *envp, int len)
{
	while (envp)
	{
		if (ft_strncmp(name, envp->name, len) == 0)
			return (envp->values); //
		envp = envp->next;
	}
	return (NULL);
}

void ft_skip_dollar(char **name)
{
	(*name)++;
	while (**name == '$')
		(*name)++;
}

char *ft_strstr(const char *haystack, const char *needle)
{
    if (!*needle)
    {
        return (char *)haystack;
    }

    for (const char *h = haystack; *h != '\0'; h++)
    {
        if (*h == *needle)
        {
            const char *h2 = h;
            const char *n = needle;
            while (*h2 && *n && *h2 == *n)
            {
                h2++;
                n++;
            }
            if (!*n)
            {
                return (char *)h;
            }
        }
    }
    return NULL;
}

char *str_replace(char *str, char *name, char *value)
{
	int len;
    char *pos;
	char *new_str;

	pos = ft_strstr(str, name);
    if (pos != NULL)
	{
        len = ft_strlen(str) + ft_strlen(value) - ft_strlen(name) + 1;
        new_str = malloc(len);
        if (new_str == NULL)
            return NULL;
		ft_strlcpy(new_str, str, pos - str + 1);
        new_str[pos - str] = '\0';
		ft_strlcat(new_str, value, len);
		ft_strlcat(new_str, pos + ft_strlen(name), len);
        return (new_str);
    }
    return (str);
}

void expand_variable(t_token *token, t_env *envp)
{
	char *name;
	char *value;
	char *new;
	int len;

	while (token)
	{
		name = token->str;
		while ((name = ft_strchr(name, '$')) != NULL)
		{
			ft_skip_dollar(&name);
			len = check_name_and_return_len(name);
			if ((*name) != '\0' && len > 0)
			{
				if (env_exists(name, envp, len))
				{
					value = get_env_value(name, envp, len);
					new = str_replace(token->str, name, value);
					free(token->str);
					token->str = new;
				}
				name += len;
			}
		}
		token = token->next;
	}
}