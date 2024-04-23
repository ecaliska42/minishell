/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:11:51 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/23 15:26:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

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

char	*get_access(char *str, t_env **envi)
{
	t_env	*path;
	int		i;
	char	*temp;
	char	*temp2;
	char	**path_values;

	i = 0;
	if (access(str, X_OK | F_OK) == 0)
		return (str);
	path = get_path(envi);
	if (!path)
		return (NULL);
	path_values = ft_split(path->values, ':');
	if (!path_values)
		return (NULL);
	while (path_values[i])
	{
		temp = ft_strdup("");
		temp = ft_strjoin(path_values[i], "/");
		temp2 = ft_strjoin(temp, str);
		free(temp);
		temp = NULL;
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		i++;
		free (temp2);
	}
	return (str);
}

int	get_check(t_mini **mini)
{
	t_parse	*node;

	node = (*mini)->parse;
	while (node)
	{
		if (node->command == NULL)
		{
			node = node -> next;
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

char	**create_command(char *str, char **cmd)
{
	int		size;
	int		i;
	char	**ret;

	i = 0;
	size = array_size(cmd);
	ret = ft_calloc(size + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = ft_strdup(cmd[i]);
		if (!ret[i])
			return (NULL);
		i++;
	}
	while (size)
	{
		free(cmd[size]);
		size--;
	}
	ret[i] = ft_strdup(str);
	if (!ret[i])
		return (NULL);
	return (ret);
}
