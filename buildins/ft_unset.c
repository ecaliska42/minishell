/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 16:58:05 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

static bool	was_found(t_env **envp, char *name)
{
	t_env	*temp;

	temp = *envp;
	while (temp)
	{
		if (name[0] == '_')
			return (false);
		if (ft_strcmp(temp->name, name) == 0)
			return (true);
		temp = temp->next;
	}
	return (false);
}

static void	delete_node(t_env **envp, char *name)
{
	t_env	*temp;
	t_env	*prev;

	temp = *envp;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->name, name) == 0)
		{
			if (prev)
				prev->next = temp->next;
			else
				*envp = temp->next;
			free_and_null((void **)&temp->name);
			temp->name = NULL;
			free_and_null((void **)&temp->values);
			temp->values = NULL;
			free_and_null((void **)&temp);
			temp = NULL;
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(t_parse **parsing, t_env **environment, t_mini **mini)
{
	t_parse	*parse;
	int		i;

	parse = *parsing;
	i = 1;
	if (first_character_is(parse->command[i], '-') == true)
	{
		write(2, "minishell: unset: '", 18);
		write(2, parse->command[i], ft_strlen(parse->command[i]));
		write(2, "': not a valid identifier\n", 26);
		(*mini)->exit_status = 2;
		return (ERROR);
	}
	while (parse->command[i])
	{
		if (was_found(environment, parse->command[i]))
			delete_node(environment, parse->command[i]);
		i++;
	}
	(*mini)->exit_status = 0;
	return (SUCCESS);
}
