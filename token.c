/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/05/01 15:39:36 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include "libraries/parsing.h"

t_token	*add_token_and_check(t_shell *shell, t_mini *ms)
{
	t_token	*last_token;

	last_token = add_new_empty_token(shell, ms);
	if (!last_token)
	{
		ft_putendl_fd("Error: Last token is null", 2);
		return (NULL);
	}
	return (last_token);
}

void	not_random(t_token *last_token, int *i)
{
	if (last_token->type == APPEND || last_token->type == HEREDOC)
		(*i)++;
	(*i)++;
}

void	handle_token_type(t_shell *shell, t_token **last_token, int **i)
{
	ft_tokenizer(shell, *last_token, **i);
	if ((*last_token)->type != RANDOM)
		not_random(*last_token, *i);
}

int	handle_pipe(t_mini *ms, t_token **last_token, char **line, int **i)
{
	if ((*last_token)->type == PIPE)
	{
		skip_spaces(*line, *i);
		if ((*line)[**i] != '\0')
		{
			*last_token = add_token_and_check(&ms->shell, ms);
			if (!*last_token)
				return (ERROR);
			handle_token_type(&ms->shell, last_token, i);
		}
	}
	return (SUCCESS);
}

int	ft_strtok(t_shell *shell, int *i, t_mini *ms)
{
	char	*line;
	t_token	*last_token;

	if (!shell)
		return (ERROR);
	line = shell->input;
	while (line[*i] != '\0')
	{
		if (ft_is_space(line[*i]) == true && line[*i] != '\0')
		{
			(*i)++;
			continue ;
		}
		last_token = add_token_and_check(shell, ms);
		if (!last_token)
			return (ERROR);
		handle_token_type(shell, &last_token, &i);
		if (handle_pipe(ms, &last_token, &line, &i) == ERROR)
			return (ERROR);
		if (not_pipe(shell, last_token, i, ms) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
