/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:06:06 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/28 19:35:57 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_everything(t_shell *shell)
{
    t_token *token;

    token = shell->tokens;
    if (!shell || !shell->tokens)
    {
        fprintf(stderr, "Error: shell, shell->input, or shell->tokens is NULL\n");
        return;
    }
    if (token)
    {
        printf("token->type: %d\n", token->type);
        printf("token->str: %s\n", token->str);
        // token = token->next;
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