/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:26 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/01 16:33:14 by ecaliska         ###   ########.fr       */
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
		{
			free(tmp->name);
			tmp->name = NULL;
		}
		if (tmp->values)
		{
			free(tmp->values);
			tmp->values = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = *lst;
	}
	return (ERROR);
}

int	increase_shell_level(char *envp, t_env **node)
{
	char	*temp;
	int		nbr;

	temp = NULL;
	temp = get_after(envp, '=');
	if (!temp)
		return (ERROR);
	nbr = ft_atoi(temp) + 1;
	if (nbr > 9999)
	{
		write(2, "warning: shell level (", 23);
		ft_putnbr_fd(nbr, 2);
		write(2, ") too high, resetting to 1\n", 28);
		nbr = 1;
	}
	if (nbr < 0)
		nbr = 0;
	(*node)->values = ft_itoa(nbr);
	if (!(*node)->values)
		return (free(temp), temp=NULL, ERROR);
	free(temp);
	temp = NULL;
	return (SUCCESS);
}

int	get_value(t_env **node, char *envp, t_env **lst)
{
	if (ft_strncmp((*node)->name, "SHLVL", 5) == 0)
	{
		if (increase_shell_level(envp, node) == ERROR)
		{
			free((*node)->name);
			(*node)->name = NULL;
			free(*node);
			*node = NULL;
			return (free_environment(lst));
		}
	}
	else
	{
		(*node)->values = get_after(envp, '=');
		if (!(*node)->values)
		{
			free((*node)->name);
			(*node)->name = NULL;
			free(*node);
			*node = NULL;
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

t_env	*get_from_env(t_env **lst, char *s)
{
	t_env	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, s) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
