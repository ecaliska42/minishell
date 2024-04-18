/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:07:45 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 17:17:46 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

char	*handle_dollar_sign(char *new, char *str, int *i, t_mini *ms)
{
	int		len;
	char	*tmp;
	char	*value;

	(*i)++;
	len = check_name_and_return_len(&str[*i]);
	tmp = ft_substr(str, *i, len);
	if (!tmp)
		return (NULL);
	(*i) += len;
	value = get_env_value(tmp, ms->env);
	if (value)
	{
		new = ft_strjoin(new, value);
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
