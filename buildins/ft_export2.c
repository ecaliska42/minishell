/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:23:42 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 14:30:50 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	print_list(t_env **list)
{
	t_env	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "_") == 0)
			tmp = tmp->next;
		else
		{
			if (tmp->values == NULL)
				printf("declare -x %s\n", tmp->name);
			else
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->values);
			tmp = tmp->next;
		}
	}
}

void	ft_swap(t_env **node1, t_env **node2)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = (*node1)->name;
	temp_value = (*node1)->values;
	(*node1)->name = (*node2)->name;
	(*node1)->values = (*node2)->values;
	(*node2)->name = temp_name;
	(*node2)->values = temp_value;
}

void	sort_list(t_env **head)
{
	t_env	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->name, tmp->next->name) > 0)
		{
			ft_swap(&tmp, &tmp->next);
			tmp = *head;
		}
		else
			tmp = tmp->next;
	}
}

void	tenv_add_back(t_env ***lst, t_env *new_l)
{
	t_env	*temp;

	if (**lst == NULL)
		**lst = new_l;
	else
	{
		temp = **lst;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_l;
	}
}

int	copied_struct(t_env **src, t_env **copy)
{
	t_env	*tmp;
	t_env	*node;

	tmp = *src;
	while (tmp)
	{
		node = malloc(sizeof(t_env));
		if (!node)
			return (ERROR);
		node->name = ft_strdup(tmp->name);
		if (!node->name)
			return (free(node), ERROR);
		if (tmp->values)
		{
			node->values = ft_strdup(tmp->values);
			if (!node->values)
				return (free(node->name), free(node), ERROR);
		}
		else
			node->values = NULL;
		node->next = NULL;
		tenv_add_back(&copy, node);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
