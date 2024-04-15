/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/15 17:26:52 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

#include "GNL/get_next_line.h"

char	*get_unique_heredoc_name(void)
{
	char	*name;
	int		dev_random;
	int		i;

	i = 0;
	dev_random = open("/dev/random", O_RDONLY);
	if (dev_random < 0)
		exit(1);
	name = malloc(sizeof(char) * 5 + 1);
	if (!name)
		exit(1);
	while (i < 5)
	{
		read(dev_random, &name[i], 1);
		name[i] = name[i] % 26 + 'a';
		i++;
	}
	name[i] = '\0';
	close(dev_random);
	//name = ft_strjoin("/tmp/", name);
	return (name);
}

void	heredoc(t_parse *node, char *end)
{
	char	*line;
	int		fd;
	char	*name;

	name = get_unique_heredoc_name();
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	// ioctl
	while (1)
	{
		// line = get_next_line(fileno(stdin));
		line = readline("> ");
		if (!line)
			break ;
		//TODO expand variables in heredoc???
		if (ft_strcmp(line, end) == 0) //should exit withc "" as eof
		{
			free(line);
			line = NULL;
			break ;
		}
		// write(fd, line, ft_strlen(line));
		// write(fd, "\n", 1);
		ft_putendl_fd(line, fd);
		free(line);
		line = NULL;
	}
	close(fd);
	node->infd = open(name, O_RDONLY);
	if (node->infd < 0)
		exit(1);
	unlink(name);
}
