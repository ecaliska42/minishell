/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/13 18:33:02 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

char *get_key(char *start, char *end)
{
    int key_len;
    char *key;

    key_len = end - start - 1;
    key = malloc(key_len + 1);
    ft_strlcpy(key, start + 1, key_len + 1);
    key[key_len] = '\0';
    return (key);
}

char *get_value(char *key)
{
    char *value;

    value = getenv(key);
    if (!value)
        value = "";
    return (value);
}

char *create_new(t_shell *shell, char *start, char *end, char *value)
{
    int key_len;
    char *new;

    key_len = end - start - 1;
    new = malloc(ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
    ft_strlcpy(new, shell->input, start - shell->input + 1);
    ft_strlcat(new, value, ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
    ft_strlcat(new, end, ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
    return (new);
}

void expand_variable(t_shell *shell)
{
    char *start;
    char *end;
    char *value;
    char *new;
    char *key;

    start = ft_strchr(shell->input, '$');
    if (!start)
        return ;
    while (start)
    {
        end = start;
        while (ft_isalnum(*end) || *end == '_')
            end++;
        key = get_key(start, end);
        value = get_value(key);
        new = create_new(shell, start, end, value);
        free(shell->input);
        shell->input = new;
        free(key);
        start = ft_strchr(shell->input, '$');
    }
}