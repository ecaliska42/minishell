/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:07:45 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/28 09:37:26 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

char	*handle_dollar_sign(char *new, char *str, int *i, t_mini *ms)
{
	int		len;
	char	*tmp;
	char	*value;
	char	*temp;

	(*i)++;
	len = check_name_and_return_len(&str[*i]);
	tmp = ft_substr(str, *i, len);
	if (!tmp)
		return (NULL);
	(*i) += len;
	value = get_env_value(tmp, ms->env);
	free_and_null((void **)&tmp);
	if (value)
	{
		temp = ft_strjoin(new, value);
		free_expansion(temp, ms->exp, ms);
		free_and_null((void **)&new);
		new = temp;
	}
	return (new);
}

char	*expand_heredoc_delimeter(char *new, char *str, int *i, t_mini *ms)
{
	while (str[*i])
	{
		if (quote_check(str[*i], &ms->shell.quotes) != 0)
		{
			(*i)++;
			while (quote_check(str[*i], &ms->shell.quotes) != 0)
			{
				new = add_char(new, str[*i]);
				free_expansion(new, ms->exp, ms);
				(*i)++;
			}
			(*i)++;
		}
		else
		{
			new = add_char(new, str[*i]);
			free_expansion(new, ms->exp, ms);
			(*i)++;
		}
	}
	return (new);
}

int	check_name_and_return_len(char *name)
{
	int	i;

	i = 0;
	if (!name || name[0] == '\0')
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*get_env_value(char *name, t_env *envp)
{
	if (!name || !envp)
		return (NULL);
	while (envp)
	{
		if (ft_strcmp(name, envp->name) == 0)
			return (envp->values);
		envp = envp->next;
	}
	return (NULL);
}
