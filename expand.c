/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:02:15 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/18 21:12:18 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"
#include "libraries/parsing.h"

int	check_name_and_return_len(char *name)
{
	int i;

	i = 0;
	if (!name)
		return (false);
	while (name[i] != '\0')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*get_env_value(char *name, t_env *envp, int len)
{
	(void)len;
	while (envp)
	{
		if (ft_strcmp(name, envp->name) == 0)
			return (envp->values);
		envp = envp->next;
	}
	return (NULL);
}

t_token	*split_value(char *value, t_token *token)
{
	char **words;
	t_token *last;
	t_token *new;
	int i;

	i = 0;
	last = token;
	words = ft_split(value, ' ');
	while (words[i] != NULL)
	{
		new = malloc(sizeof(t_token));
		new->str = words[i];
		new->next = NULL;
		new->type = token->type;
		last->next = new;
		last = new;
		i++;
	}
	free(words);
	return (last);
}

t_token	*expand_variable(t_token *token, t_env *envp, char *quotes)
{
    
}

replace_variable_name()
{
    
}

get_exit_code()
{
    
}



void	*skip_squotes_expanding(t_token *token, t_env *envp, char *quotes)
{
	char	*ptr;
    int i;

    i = 0;
	ptr = token->str;
	if (quote_check(ptr[i], quotes) == 1) //squote
    {
        while (ptr[i] != '\0' && ptr[i] != '\'')
            i++;
        if (ptr[i] == '\'')
        {
            quote_check(ptr[i], quotes);
            i++;
        }
    }
}

void	dquotes_expanding(t_token *token, t_env *envp, char *quotes)
{
    char	*ptr;
    int i;

    i = 0;
    ptr = token->str;
    if (quote_check(ptr[i], quotes) == 2) //dquote
    {
        while (ptr[i] != '\0' && ptr[i] != '\"')
        {
            if (ptr[i] == '$')
            {
                i++;
                if (ptr[i] == '?')
                    get_exit_code();
                else if (ft_isalpha(ptr[i]) || ptr[i] == '_')
                    replace_variable_name();
            }
            i++;
        }
        if (ptr[i] == '\"')
            quote_check(ptr[i], quotes);
    }
}

// void	expansion(t_token *token, t_env *envp, char *quotes)
// {
// 	while (token != NULL)
// 	{
// 		token = expand_variable(token, envp, CLOSED);
// 		token = token->next;
// 	}
// }

void	expand_var(t_token *token, t_env *envp)
{
    char	quotes;

    quotes = CLOSED;
    while (token != NULL)
    {
        if (quote_check(*token->str, &quotes) == 1)
            skip_squotes_expanding(token, envp, &quotes);
        else if (quote_check(*token->str, &quotes) == 2)
            dquotes_expanding(token, envp, &quotes);
        else
            expansion(token, envp, &quotes);
        token = token->next;
    }
}