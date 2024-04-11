/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/11 16:11:02 by ecaliska         ###   ########.fr       */
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
			free(temp->name);
			temp->name = NULL;
			free(temp->values);
			temp->values = NULL;
			free(temp);
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
	while (parse->command[i])
	{
		if (was_found(environment, parse->command[i]))
			delete_node(environment, parse->command[i]);
		i++;
	}
	(*mini)->exit_status = 0;
	return (SUCCESS);
}
