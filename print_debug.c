/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:06 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/02 13:47:51 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"

// void	free_tokens(t_token **tokens)
// {
// 	t_token	*tmp;

// 	while (*tokens != NULL)
// 	{
// 		tmp = *tokens;
// 		*tokens = (*tokens)->next;
// 		if (tmp->str)
// 		{
// 			printf("freeing tmp->str:%s\n", tmp->str);
// 			free(tmp->str);
// 			tmp->str = NULL;
// 		}
// 		if (tmp)
// 		{
// 			free(tmp);
// 			tmp = NULL;
// 		}
// 	}
// }

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens != NULL)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->str != NULL)
		{
			// printf("freeing tmp->str:%s\n", tmp->str);
			free(tmp->str);
		}
		free(tmp);
	}
}

void	print_everything(t_shell *shell)
{
	t_token	*token;

	token = shell->tokens;
	if (!shell)
	{
		ft_putstr_fd("Error: shell, shell->input, or shell->tokens is NULL\n",
			2);
		return ;
	}
	if (!shell->tokens)
	{
		ft_putstr_fd("Error: shell->tokens is NULL\n", 2);
		return ;
	}
	while (token)
	{
		printf("token->str:%s\n", token->str);
		printf("token->type:%d\n", token->type);
		printf("ambiguous_redirect:%d\n\n", token->ambiguous);
		token = token->next;
	}
}
