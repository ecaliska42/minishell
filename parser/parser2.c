/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:11:51 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/24 18:59:55 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

t_env	*get_path(t_env **envi)
{
	t_env	*temp;

	temp = *envi;
	while (temp)
	{
		if (ft_strncmp(temp->name, "PATH", 4) == 0)
			break ;
		temp = temp -> next;
	}
	if (!temp)
		return (NULL);
	return (temp);
}

char	*do_while_access(char **path_values, char *str)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	while (path_values[i])
	{
		// temp = ft_strdup("");
		// if (!temp)
		// 	return (NULL);
		temp = ft_strjoin(path_values[i], "/");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin(temp, str);
		if (!temp2)
			return (free(temp), NULL);
		free(temp);
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		i++;
		free (temp2);
	}
	return (str);
}

char	*get_access(char *str, t_env **envi)
{
	t_env	*path;
	char	*temp2;
	char	**path_values;

	if (access(str, X_OK | F_OK) == 0)
	{
		temp2 = ft_strdup(str);
		return (temp2);
	}
	path = get_path(envi);
	if (!path)
		return (NULL);
	path_values = ft_split(path->values, ':');
	if (!path_values)
		return (NULL);
	temp2 = do_while_access(path_values, str);
	free_double(path_values);
	if (!temp2)
		return (NULL);
	return (temp2);
}

int	get_check(t_mini **mini)
{
	t_parse	*node;

	node = (*mini)->parse;
	while (node)
	{
		if (node->command == NULL)
		{
			node = node->next;
			continue ;
		}
		node->check = get_access(node->command[0], &(*mini)->env);
		if (!node->check)
			return (ERROR);
		node = node -> next;
	}
	return (SUCCESS);
}

void	add_back(t_parse **com, t_parse *node)
{
	t_parse	*temp;

	if (*com == NULL)
		*com = node;
	else
	{
		temp = *com;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = node;
	}
	temp = *com;
}
