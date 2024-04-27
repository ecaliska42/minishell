/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:14:17 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/27 11:39:43 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void	free_and_null(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
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

void	free_mini(t_mini **mini)
{
	free_tokens(&(*mini)->shell.tokens);
	free_and_null((void **)&(*mini)->shell.input);
	free_parsing_node(&(*mini)->parse);
	free_exe(&(*mini)->exe);
}
