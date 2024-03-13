/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:06 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/13 23:49:11 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/parsing.h"

void free_tokens(t_token **tokens)
{
	t_token *tmp;

	tmp = *tokens;
	while (*tokens)
	{
		*tokens = (*tokens)->next;
		// if (tmp->str)
		// 	printf("tmp->str:%s\n", tmp->str);
		// if (tmp->type)
		// 	printf("tmp->type:%d\n", tmp->type);
		if (tmp->str)
		{
			free(tmp->str);
			tmp->str = NULL;
		}
		if (tmp)
		{
			free(tmp);
		}
		tmp = *tokens;
	}
}

void print_everything(t_shell *shell)
{
    t_token *token;

    token = shell->tokens;
    if (!shell)
    {
        ft_putstr_fd("Error: shell, shell->input, or shell->tokens is NULL\n", 2);
        return;
    }
    if (!shell->tokens)
    {
        ft_putstr_fd("Error: shell->tokens is NULL\n", 2);
        return;
    }
    while (token)
    {
        printf("token->str:%s\n", token->str);
        printf("token->type:%d\n\n", token->type);
        token = token->next;
    }
}
