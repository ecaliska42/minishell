/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:26 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/16 19:09:49 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

int	free_environment(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	if (!lst)
		return (ERROR);
	while (*lst)
	{
		*lst = (*lst)->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->values)
			free(tmp->values);
		if (tmp)
			free(tmp);
		tmp = *lst;
	}
	return (ERROR);
}

int	increase_shell_level(char *envp, t_env **node)
{
	char	*temp;

	temp = NULL;
	temp = get_after(envp, '=');
	if (!temp)
		return (ERROR);
	(*node)->values = ft_itoa(ft_atoi(temp) + 1);
	if (!(*node)->values)
		return (free(temp), ERROR);
	free(temp);
	return (SUCCESS);
}

int	get_value(t_env **node, char *envp, t_env **lst)
{
	if (strncmp((*node)->name, "SHLVL", 5) == 0)
	{
		if (increase_shell_level(envp, node) == ERROR)
		{
			free((*node)->name);
			free(*node);
			return (free_environment(lst));
		}
	}
	else
	{
		(*node)->values = get_after(envp, '=');
		if (!(*node)->values)
		{
			free((*node)->name);
			free(*node);
			return (free_environment(lst));
		}
	}
	return (SUCCESS);
}

//?PROTECTION DONE HERE SHOULD BE NO FUNCHECK ERRORS
int	copy_environment(char **envp, t_env **lst)
{
	int		i;
	t_env	*new_node;
	t_env	*tail;

	i = 0;
	*lst = NULL;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (free_environment(lst));
		new_node->name = get_till(envp[i], '=');
		if (!new_node->name)
			return (free(new_node), free_environment(lst));
		if (get_value(&new_node, envp[i], lst) == ERROR)
			return (ERROR);
		new_node->next = NULL;
		if (*lst == NULL)
			*lst = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (SUCCESS);
}