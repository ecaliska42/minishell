/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:11:51 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:10:28 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

t_env	*get_path(t_env **envi)
{
	t_env	*temp;

	temp = *envi;
	while (temp)
	{
		if (ft_strcmp(temp->name, "PATH") == 0)
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
	char	*ret;
	char	*temp2;

	i = 0;
	while (path_values[i])
	{
		temp = ft_strjoin(path_values[i], "/");
		if (!temp)
			return (NULL);
		temp2 = ft_strjoin(temp, str);
		if (!temp2)
			return (free_and_null((void **)&temp), NULL);
		free_and_null((void **)&temp);
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		i++;
		free_and_null((void **)&temp2);
	}
	ret = ft_strdup(str);
	return (ret);
}

char	*get_current(char *str, t_mini **mini)
{
	char	*current_pwd;
	char	*temp;

	current_pwd = malloc(FILENAME_MAX);
	check_malloc_exit(current_pwd, (*mini));
	if (getcwd(current_pwd, FILENAME_MAX) == NULL)
	{
		perror("getcwd");
		free_and_null((void **)&current_pwd);
		return (NULL);
	}
	temp = current_pwd;
	current_pwd = ft_strjoin(current_pwd, "/");
	free_and_null((void **)&temp);
	temp = current_pwd;
	current_pwd = ft_strjoin(current_pwd, str);
	free_and_null((void **)&temp);
	return (current_pwd);
}

char	*get_access(char *str, t_env **envi, t_mini **mini)
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
	{
		temp2 = get_current(str, mini);
		return (temp2);
	}
	path_values = ft_split(path->values, ':');
	if (!path_values)
		return (NULL);
	temp2 = do_while_access(path_values, str);
	check_malloc_exit(temp2, *mini);
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
		node->check = get_access(node->command[0], &(*mini)->env, mini);
		if (!node->check)
			return (ERROR);
		node = node -> next;
	}
	return (SUCCESS);
}
