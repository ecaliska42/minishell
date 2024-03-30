/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/30 20:20:53 by ecaliska         ###   ########.fr       */
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
	int		i;
	char	*name;

	i = 0;
	name = get_unique_heredoc_name();
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		//TODO expand variables in heredoc???
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
	node->infd = open(name, O_RDONLY);
	if (node->infd < 0)
		exit(1);
	unlink(name);
}
