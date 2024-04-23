/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:28:43 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/23 17:47:30 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_list(t_env **head)
{
	t_env	*tmp;

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

int	print_export(t_env *head)
{
	t_env	*copy;

	copy = NULL;
	copied_struct(&head, &copy);
	sort_list(&copy);
	print_list(&copy);
	free_list(&copy);
	return (SUCCESS);
}

int	env_addback(t_env **head, char *name, char *value)
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

int	get_before_after(char **before, char **after, char *s)
{
	*before = get_till(s, '=');
	if (!before)
		return (ERROR);
	*after = get_after(s, '=');
	if (!after)
		return (free(before), before = NULL, ERROR);
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
