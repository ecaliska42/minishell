/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:43:38 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/24 18:51:09 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->str != NULL)
		 	free_and_null((void **)&tmp->str);
		free(tmp);
	}
}

void	check_malloc_exit(void *ptr, t_mini *mini)
{
	if (ptr == NULL)
	{
		ft_putendl_fd("Malloc failed", 2);
		free_tokens(&mini->shell.tokens);
		free_and_null((void **)&mini->shell.input);
		free_environment(&mini->env);
		free_parsing_node(&mini->parse);
		exit(EXIT_FAILURE);
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
		if (ex_struct->fd[i])
		{
			while (ex_struct->fd[i])
			{
				free_and_null((void **)&ex_struct->fd[i]);
				i++;
			}
		}
		free_and_null((void **)&ex_struct->fd);
	}
	free_and_null((void **)&ex_struct->id);
}

void	free_mini_and_exit(t_mini **mini)
{
	free_tokens(&(*mini)->shell.tokens);
	free_and_null((void **)&(*mini)->shell.input);
	free_environment(&(*mini)->env);
	free_parsing_node(&(*mini)->parse);
	free_tokens(&(*mini)->shell.tokens);
	free_exe(&(*mini)->exe);
	exit((*mini)->exit_status);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free_and_null((void **)&str[i]);
		i++;
	}
	free_and_null((void **)&str);
}