/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/19 18:38:28 by ecaliska         ###   ########.fr       */
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

char	*expand_heredoc(char *str, t_env *envp, t_mini **mini)
{
	int		len;
	char	*tmp;
	t_mini	*ms = *mini;
	char	*value;

	int i = 0;
	char *new = ft_strdup("");
	while (str[i])
	{
		while (str[i] && str[i] != '$')
		{
			new = add_char(new, str[i]);
			(i)++;
		}
		if ((ft_is_dollar(str[i])) && (str[(i) + 1] && (str[(i)
					+ 1] != '$')))
		{
			if (str[(i) + 1] == '?')
				replace_exit_code(str, &new, &i, ms);
			(i)++;
			len = check_name_and_return_len(&str[i]);
			tmp = ft_substr(str, i, len);
			if (!tmp)
				return (NULL);
			(i) += len;
			if ((value = get_env_value(tmp, envp)) != NULL)
			{
				new = ft_strjoin(new, value);
			}
		}
		while (str[i] && str[i] != '$' && str[i])
		{
			new = add_char(new, str[i]);
			(i)++;
		}
	}
	return (new);
}

void	heredoc(t_parse *node, char *end, bool expand, t_mini **mini)
{
	char	*line;
	int		fd;
	char	*name;

	name = get_unique_heredoc_name();
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	signal_handler(4, *mini);
	while (1)
	{
		if (g_sig)
			break ;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, end) == 0) //should exit withc "" as eof
		{
			free(line);
			line = NULL;
			break ;
		}
		if (expand == true)
			line = expand_heredoc(line, (*mini)->env, mini);
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
