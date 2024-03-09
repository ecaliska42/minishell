/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:06 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/09 18:58:42 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
        free(tmp->str);
		tmp->str = NULL;
		free(tmp);
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


int ft_strcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
    {
        ft_putstr_fd("Error: s1 or s2 is NULL\n", 2);
        return (-1);
    }
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*s1 - *s2);
}