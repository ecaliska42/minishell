/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:25:26 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:32:04 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

//int	free_environment(t_env **lst)
//{
//	t_env	*tmp;
//
//	tmp = *lst;
//	if (!lst)
//		return (ERROR);
//	while (*lst)
//	{
//		tmp = *lst;
//		*lst = (*lst)->next;
//		if (tmp->name)
//			free_and_null((void **)&tmp->name);
//		if (tmp->values)
//			free_and_null((void **)&tmp->values);
//		if (tmp)
//			free_and_null((void **)&tmp);
//	}
//	*lst = NULL;
//	return (ERROR);
//}

int	free_environment(t_env **lst)
{
    t_env	*tmp;
    t_env	*next;

    if (!lst || !*lst)
        return (ERROR);

    tmp = *lst;
    while (tmp)
    {
        next = tmp->next;
        if (tmp->name)
            free_and_null((void **)&tmp->name);
        if (tmp->values)
            free_and_null((void **)&tmp->values);
        free_and_null((void **)&tmp);
        tmp = next;
    }
    *lst = NULL;
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
	if (nbr > 999)
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
		return (free_and_null((void **)&temp), ERROR);
	free_and_null((void **)&temp);
	temp = NULL;
	return (SUCCESS);
}

int	get_value(t_env **node, char *envp, t_env **lst)
{
	if (ft_strncmp((*node)->name, "SHLVL", 5) == 0)
	{
		if (increase_shell_level(envp, node) == ERROR)
		{
			free_and_null((void **)&(*node)->name);
			free_and_null((void **)&*node);
			return (free_environment(lst));
		}
	}
	else
	{
		(*node)->values = get_after(envp, '=');
		if (!(*node)->values)
		{
			free_and_null((void **)&(*node)->name);
			free_and_null((void **)&*node);
			return (free_environment(lst));
		}
	}
	return (SUCCESS);
}

int	copy_environment(char **envp, t_env **lst)
{
	int		i;
	t_env	*new_node;
	t_env	*tail;

	i = 0;
	*lst = NULL;
	while (envp[i])
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (!new_node)
			return (free_environment(lst));
		new_node->name = get_till(envp[i], '=');
		if (!new_node->name)
			return (free_and_null((void **)&new_node), free_environment(lst));
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
