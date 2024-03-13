/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:23:48 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/14 00:02:38 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

// char *get_key(char *start, char *end)
// {
//     int key_len;
//     char *key;

//     key_len = end - start - 1;
//     key = malloc(key_len + 1);
//     ft_strlcpy(key, start + 1, key_len + 1);
//     key[key_len] = '\0';
//     return (key);
// }

// char *get_value(char *key)
// {
//     char *value;

//     value = getenv(key);
//     if (!value)
//         value = "";
//     return (value);
// }

// char *create_new(t_shell *shell, char *start, char *end, char *value)
// {
//     int key_len;
//     char *new;

//     key_len = end - start - 1;
//     new = malloc(ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
//     ft_strlcpy(new, shell->input, start - shell->input + 1);
//     ft_strlcat(new, value, ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
//     ft_strlcat(new, end, ft_strlen(shell->input) - key_len + ft_strlen(value) + 1);
//     return (new);
// }

// void expand_variable(t_shell *shell, t_env *envp)
// {
//     char *start;
//     char *end;
//     char *value;
//     char *new;
//     char *key;

//     start = ft_strchr(shell->input, '$');
//     if (!start)
//         return ;
//     while (start)
//     {
//         end = start;
//         while (ft_isalnum(*end) || *end == '_')
//             end++;
//         key = get_key(start, end);
//         value = get_value(key);
//         new = create_new(shell, start, end, value);
//         free(shell->input);
//         shell->input = new;
//         free(key);
//         start = ft_strchr(shell->input, '$');
//     }
// }

// tokens--
// find $
// check if env =
// change input from env to token->str  hel$a   => hello not is single

// if not
//     -   if number, delete dollar and first number
//     -   change with \n


int get_input_of_env(char *i)
{
	
}

//checks if env name is valid and returns the length of the env name
// (if valid_env_name != 0)
bool check_name_and_return_len(char *name)
{
	int i;

	i = 0;
	if (!name)
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (i);
}

bool env_exists(char *name, t_env *envp) // use ft_strcmp
{
	while (envp)
	{
		if (ft_strcmp(name, envp->name) == 0)
			return (true);
		envp = envp->next;
	}
	return (false);
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

void expand_variable(t_shell *shell, t_env *envp)
{

}