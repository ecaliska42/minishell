/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:07 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/30 20:27:23 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static void	print_list(t_env **list)
{
	t_env	*tmp;
	
	tmp = *list;
	while (tmp)
	{
		// tmp = *list;
		if (ft_strcmp(tmp->name, "_") == 0)
			tmp=tmp->next;
		else
		{
			printf("ShellMate: declare -x %s=\"%s\"\n", tmp->name, tmp->values);
			tmp = tmp->next;
		}
	}
}

static void ft_swap(t_env **node1, t_env **node2)
{
	char *temp_name;
	char *temp_value;
	
	temp_name = (*node1)->name;
	temp_value = (*node1)->values;
	(*node1)->name = (*node2)->name;
	(*node1)->values = (*node2)->values;
	(*node2)->name = temp_name;
	(*node2)->values = temp_value;
}

static void	sort_list(t_env **head)
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

static int copied_struct(t_env **src, t_env **copy)
{	
	t_env *tmp;

	tmp = *src;
	while (tmp)
	{
		t_env *node = malloc(sizeof(t_env));
		if (!node)
			return (ERROR);
		node->name = ft_strdup(tmp->name);
		if (!node->name)
		{
			free(node);
			return (ERROR);
		}
		node->values = ft_strdup(tmp->values);
		if (!node->values)
		{
			free(node->name);
			free(node);
			return (ERROR);
		}
		node->next = NULL;
		tenv_add_back(&copy, node);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void free_list(t_env **head)
{
	t_env *tmp;
	t_env *next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->values);
		free(tmp);
		tmp = next;
	}
}

static int print_export(t_env *head)
{
	t_env *copy = NULL;
	copied_struct(&head, &copy);
	sort_list(&copy);
	print_list(&copy);
	free_list(&copy);
	return (SUCCESS);
}

static int	env_addback(t_env **head, char *name, char *value)
{
	t_env	*node;
	t_env	*tmp;

	tmp = *head;
	while (tmp->next && ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (ft_strcmp(tmp->name, name) == 0)
	{
		tmp->values = value;
		return (SUCCESS);
	}
	node = malloc(sizeof(t_env));
	if (!node)
		return (ERROR);
	node->name = name;
	node->values = value;
	node->next = NULL;
	tmp->next = node;
	return (SUCCESS);
}

static int get_before_after(char **before, char **after, char *s)
{
	*before = get_till(s, '=');
	if (!before)
		return (ERROR);
	*after = get_after(s, '=');
	if (!after)
		return (free(before), ERROR);
	return (SUCCESS);
}

int	ft_export(t_env **lst, t_parse **node)
{
	t_env	*envp;
	t_parse	*command;
	char	*before;
	char	*after;
	int		i;

	i = 1;
	envp = *lst;
	command = *node;
	if (array_size(command->command) < 2)
		return (print_export(envp));
	while (command->command[i])
	{
		if (get_before_after(&before, &after, command->command[i]) == ERROR)
			return (ERROR);
		if (ft_strchr(command->command[i], '=') != NULL && ft_strlen(command->command[i]) == 1)
			return (write(2, "export : '=': not a valid identifier\n", 38));
		if (ft_strchr(command->command[i], '=') != NULL)
		{
			if (ft_strlen(before) == 0 || is_alpha_numbers(before) == false)
			{
				write(2, "export: ", 9);
				write(2, command->command[i], ft_strlen(command->command[i]));
				write(2, "': not a valid identifier\n", 26);
				i++;
				continue;
			}
			env_addback(&envp, before, after);
		}
		else
			env_addback(&envp, before, NULL);
		i++;
	}
	return 0;
}

//TODO only characters are allowed!