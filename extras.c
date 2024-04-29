/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 16:33:50 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 16:52:10 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/parsing.h"
#include "libraries/minishell.h"

t_token	*add_new_empty_token(t_shell *shell)
{
	t_token	*last_token;

	if (token_add(&shell->tokens) == -1)
	{
		ft_putendl_fd("Error: Token add failed", 2);
		return (NULL);
	}
	last_token = get_last_token(&shell->tokens);
	return (last_token);
}

void	norm_helper(char *str, t_expand *exp, t_mini *ms)
{
	while (str[exp->i] && str[exp->i] != '$')
	{
		exp->newest = add_char(exp->newest, str[exp->i]);
		free_expansion(exp->newest, ms->exp, ms);
		(exp->i)++;
	}
}

void	norm_helper_two(char *str, t_expand *exp, t_mini *ms)
{
	if (ft_is_dollar(str[exp->i]))
	{
		exp->newest = add_char(exp->newest, str[exp->i]);
		exp->i++;
	}
	while (str[exp->i] && str[exp->i] != '$' && str[exp->i])
	{
		exp->newest = add_char(exp->newest, str[exp->i]);
		free_expansion(exp->newest, ms->exp, ms);
		(exp->i)++;
	}
}
