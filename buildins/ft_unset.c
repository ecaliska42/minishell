/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/24 16:19:54 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"
#include <ncurses.h>
#include <stdbool.h>

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

void	delete_node(t_env **envp, char *name)
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
			free(temp->values);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int	ft_unset(t_token **tokens, t_parse **parsing, t_env **environment)
{
	t_token *token;
	t_env	*envp;
	t_parse	*parse;
	int		i;

	if (!tokens || !parsing)
		return (ERROR);
	token = *tokens;
	envp = *environment;
	parse = *parsing;
	i = 1;
	while (parse->command[i])
	{
		if (was_found(environment, parse->command[i]))
			delete_node(environment, parse->command[i]);
		i++;
	}
	//ft_putendl_fd("IN UNSET", 2);
	return (SUCCESS);
}
