/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:26:46 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/18 16:34:33 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/parsing.h"

t_token	*add_token_and_check(t_shell *shell)
{
	t_token	*last_token;

	last_token = add_new_empty_token(shell);
	if (!last_token)
	{
		write(2, "Error: Token add failed\n", 25);
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

int	handle_pipe(t_shell *shell, t_token **last_token, char **line, int **i)
{
	if ((*last_token)->type == PIPE)
	{
		skip_spaces(*line, *i);
		if ((*line)[**i] != '\0')
		{
			*last_token = add_token_and_check(shell);
			if (!*last_token)
				return (ERROR);
			handle_token_type(shell, last_token, i);
		}
	}
	return (SUCCESS);
}

int	ft_strtok(t_shell *shell, int *i)
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
		last_token = add_token_and_check(shell);
		if (!last_token)
			return (ERROR);
		handle_token_type(shell, &last_token, &i);
		if (handle_pipe(shell, &last_token, &line, &i) == ERROR)
			return (ERROR);
		if (not_pipe(shell, last_token, i) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
