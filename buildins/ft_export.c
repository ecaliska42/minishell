/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:07 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 13:50:53 by ecaliska         ###   ########.fr       */
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
			tmp=tmp->next;
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

void ft_swap(t_env **node1, t_env **node2)
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
		if (tmp->values)
		{
			node->values = ft_strdup(tmp->values);
			if (!node->values)
			{
				free(node->name);
				free(node);
				return (ERROR);
			}	
		}
		else
			node->values = NULL;
		node->next = NULL;
		tenv_add_back(&copy, node);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void free_list(t_env **head)
{
	t_env *tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->name);
		tmp->name = NULL;
		free(tmp->values);
		tmp->values = NULL;
		free(tmp);
		tmp = NULL;
		tmp = *head;
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
	node->name = ft_strdup(name);
	if (!node->name)
	{
		free(node);
		return (ERROR);
	}
	free(name);
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
		return (free(before), before=NULL, ERROR);
	return (SUCCESS);
}

int	no_options(t_mini **mini, t_parse *command)
{
	write(2, "export: -", 9);
	write(2, &command->command[1][1], 1);
	write(2, ": no options are allowed\n", 26);
	(*mini)->exit_status = 2;
	return (ERROR);
}

int	only_equal(t_mini **mini)
{
	write(2, "export : '=': not a valid identifier\n", 38);
	(*mini)->exit_status = 1;
	return (ERROR);
}

void	export_error(char *command, int *i, int *fail)
{
	write(2, "export: '", 10);
	write(2, command, ft_strlen(command));
	write(2, "': not a valid identifier\n", 26);
	(*i)++;
	*fail = 1;
}

void	set_exit_status(int fail, t_mini **mini)
{
	if (fail == 1)
		(*mini)->exit_status = 1;
	else
		(*mini)->exit_status = 0;
}

int	add_export(t_env *envp, char *before, char *after, char *command)
{
	if (ft_strchr(command, '=') != NULL)
		env_addback(&envp, before, after);
	else
		env_addback(&envp, before, NULL);
	return (SUCCESS);
}

typedef struct t_export{
	t_env *envp;
	t_parse	*command;
	char *before;
	char *after;
	int	fail;
	int	i;
}	t_export;

int	while_loop(t_export *expo, t_mini **mini)
{
	while (expo->command->command[expo->i])
	{
		if (get_before_after(&expo->before, &expo->after, expo->command->command[expo->i]) == ERROR)
			return (ERROR);
		if (ft_strchr(expo->command->command[expo->i], '=') != NULL && ft_strlen(expo->command->command[expo->i]) == 1)
			return (only_equal(mini));
		if (ft_strlen(expo->before) == 0 || is_alpha_numbers(expo->before) == false)
		{
			export_error(expo->command->command[expo->i], &expo->i, &expo->fail);
			continue;
		}
		add_export(expo->envp, expo->before, expo->after, expo->command->command[expo->i]);
		expo->i++;
	}
	return (SUCCESS);
}

int	ft_export(t_env **lst, t_parse **node, t_mini **mini)
{
	t_export expo;

	expo.i = 1;
	expo.envp = *lst;
	expo.command = *node;
	expo.fail = 0;
	if (array_size(expo.command->command) < 2)
		return (print_export(expo.envp));
	if (expo.command->command[1][0] == '-' && ft_strlen(expo.command->command[1]) > 1)
		return (no_options(mini, expo.command));
	if (while_loop(&expo, mini) == ERROR)
		return (ERROR);
	set_exit_status(expo.fail, mini);
	return 0;
}

//? export a=hello b=world =adf c=again