/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:02:15 by mesenyur          #+#    #+#             */
/*   Updated: 2024/03/17 16:29:46 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"

int	check_name_and_return_len(char *name)
// returns the len of the name
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
// returns the value of the variable
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
// splits the value and creates new tokens
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
		new->type = 5;
		last->next = new;
		last = new;
		i++;
	}
	free(words);
	return (last); // return last token of the new tokens created from value
}

void	replace_variable_in_token(t_token *token, char *name)
{
}

t_token	*expand_token_and_remove_quotes(t_token *token, t_env *envp, char *quotes)
{
	int i;
	int k;
	int len;
	char *new_str;

	i = 0;
	k = 0;
	len = ft_strlen(token->str + 1);
	new_str = malloc(len * sizeof(char) * 10);
	quotes = CLOSED;
	while (token->str)
	{
		quote_check(token->str[i], quotes);
		if (token->str[i] == S_QUOTE)
		{
			i++;
			while (token->str[i] != S_QUOTE)
			{
				new_str[k] = token->str[i];
				i++;
				k++;
			}
			if (token->str[i] == S_QUOTE)
				i++;
			quotes = CLOSED;
			new_str[k] = '\0';
		} // single quotes removed new_str will be the new token->str in the end
		if (token->str[i] == D_QUOTE)
		{
			quote_check(token->str[i], quotes);
			i++;
			while (token->str[i] != D_QUOTE)
			{
				new_str[k] = token->str[i];
				i++;
				k++;
			}

		}
		if // check if token->str has a $ in it
		{
			if // $ + 1 is space or NULL
				// leave dollar sign as it is
			else if // $ + 1 is number
				// remove dollar sign and the nbr  $1234 -> 234
			else if // $ + 1 is '?'
				// get the value of the $? (from envp?) and replace it
		}

		// check next token "token = token->next;"
	}
	}



	last_token = split_value(value, token);
}

void	expand_variable(t_token *token, t_env *envp)
{
	while (token != NULL)
	{
		token = expand_token(token, envp);
		token = token->next;
	}
}
