/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/11 20:02:55 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	heredoc(t_parse *node, char *end)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	node->infd = open("heredoc", O_RDONLY);
	if (node->infd < 0)
		exit(1);
}