/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:43:38 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 20:34:51 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->str != NULL)
			free_and_null((void **)&tmp->str);
		free_and_null((void **)&tmp);
	}
}

void	free_exe(t_exe *ex_struct)
{
	int	i;

	i = 0;
	if (!ex_struct)
		return ;
	if (ex_struct->fd)
	{
		while (ex_struct->fd[i])
		{
			free_and_null((void **)&ex_struct->fd[i]);
			i++;
		}
	}
	if (ex_struct->fd)
		free_and_null((void **)&ex_struct->fd);
	free_and_null((void **)&ex_struct->id);
}

void	free_expansion(void *ptr, t_expansion *exp, t_mini *ms)
{
	if (ptr == NULL)
	{
		free_and_null((void **)&exp->tmp);
		free_and_null((void **)&exp->value);
		free_and_null((void **)&exp->joker);
		free_and_null((void **)&exp->tmp_i);
		check_malloc_exit(NULL, ms);
	}
}

void	check_malloc_exit(void *ptr, t_mini *mini)
{
	if (ptr == NULL)
	{
		free_and_null((void **)&mini->shell.input);
		free_exe(&mini->exe);
		free_parsing_node(&mini->parse);
		free_environment(&mini->env);
		free_tokens(&mini->shell.tokens);
		exit(mini->exit_status);
	}
}
