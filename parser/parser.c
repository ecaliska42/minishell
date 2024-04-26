/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 16:57:17 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

t_parse	*is_pipe(t_mini **mini, t_parse **node)
{
	(*mini)->exe.pipecount++;
	add_back(&(*mini)->parse, *node);
	*node = malloc(sizeof(t_parse));
	if (!*node)
	{
		ft_putendl_fd("malloc parser.c", 2);
		return (NULL);
	}
	ft_bzero(*node, sizeof(t_parse));
	return (*node);
}

void	is_file(t_token **tmp, t_parse ***node, t_mini **mini)
{
	if ((*tmp)->type == INPUT && ft_strlen((*tmp)->str) > 0)
		is_input((*tmp)->str, &node, mini);
	else if ((*tmp)->type == OUTPUT && ft_strlen((*tmp)->str) > 0
		&& (**node)->execute == EXECUTE)
		is_output((*tmp), &node);
	else if ((*tmp)->type == APPEND && ft_strlen((*tmp)->str) > 0)
		is_append((*tmp), &node);
	else if ((*tmp)->type == HEREDOC)
		heredoc(**node, (*tmp)->str, (*tmp)->flag_exp, mini);
}

int	while_loop_parser(t_token *tmp, t_parse **node, t_mini *mini)
{
	while (tmp)
	{
		is_file(&tmp, &node, &mini);
		if (tmp->type == RANDOM)
		{
			if (is_random(tmp, &node) == ERROR)
				return (ERROR);
		}
		else if (tmp->type == PIPE)
		{
			*node = is_pipe(&mini, node);
			if (!node)
				return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

char	**create_command(char *str, char **cmd)
{
	int		size;
	int		i;
	char	**ret;

	i = 0;
	size = array_size(cmd);
	ret = ft_calloc(size + 2, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = ft_strdup(cmd[i]);
		if (!ret[i])
			return (NULL);
		i++;
	}
	while (size--)
		free_and_null((void **)&cmd[size]);
	free_and_null((void **)&cmd);
	ret[i] = ft_strdup(str);
	if (!ret[i])
		return (NULL);
	return (ret);
}

int	prepare_for_execution(t_mini **minishell)
{
	t_parse	*node;
	t_token	*tmp;
	t_mini	*mini;

	mini = *minishell;
	tmp = mini->shell.tokens;
	mini->exe.pipecount = 0;
	node = malloc(sizeof(t_parse));
	if (!node)
		return (return_write("malloc parser.c", ERROR));
	ft_bzero(node, sizeof(*node));
	if (while_loop_parser(tmp, &node, mini) == ERROR)
		return (ERROR);
	add_back(&mini->parse, node);
	get_check(&mini);
	execute(&mini);
	free_parsing_node(&mini->parse);
	return (SUCCESS);
}
