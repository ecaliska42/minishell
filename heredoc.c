/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/10 16:36:05 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

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
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		//TODO expand variables in heredoc???
		if (ft_strcmp(line, end) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close(fd);
	node->infd = open(name, O_RDONLY);
	if (node->infd < 0)
		exit(1);
	unlink(name);
}
