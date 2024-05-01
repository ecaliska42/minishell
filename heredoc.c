/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:29:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/01 13:14:40 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

//name = ft_strjoin("/tmp/", name); //ONLY IF THE NAME SHOULD BE 
//SHOWN IN FILES OR BE INVICIBLE IN TEMPORARY
char	*get_unique_heredoc_name(t_mini **mini)
{
	char	*name;
	char	*tmp;
	int		dev_random;
	int		i;

	i = 0;
	dev_random = open("/dev/random", O_RDONLY);
	if (dev_random < 0)
		free_mini_and_exit(mini);
	tmp = ft_calloc(5 + 1, sizeof(char));//!IS WORKING
	if (!tmp)
	{
		close (dev_random);
		return (NULL);
		// free_mini_and_exit(mini);
		free_expansion(tmp, (*mini)->exp, *mini);
	}
	while (i < 5)
	{
		read(dev_random, &tmp[i], 1);
		tmp[i] = tmp[i] % 26 + 'a';
		i++;
	}
	close(dev_random);
	name = ft_strjoin("/tmp/", tmp);
	free_expansion(name, (*mini)->exp, *mini);
	free_and_null((void **)&tmp);
	if (!name)
		return (NULL);
	return (name);
}

int	is_dollar_hd(t_expand *exp, char *str, t_mini *ms, t_env *envp)
{
	char	*tmp;

	if (str[(exp->i) + 1] == '?')
		replace_exit_code(str, &exp->newest, &exp->i, ms);
	(exp->i)++;
	exp->len = check_name_and_return_len(&str[exp->i]);
	exp->tmp = ft_substr(str, exp->i, exp->len);
	if (!exp->tmp)
		return (ERROR);
	(exp->i) += exp->len;
	exp->value = get_env_value(exp->tmp, envp);
	if (exp->value == NULL)
		return (free_and_null((void **)&exp->tmp), SUCCESS);
	tmp = ft_strjoin(exp->newest, exp->value);
	if (!tmp)
		return (free_and_null((void **)&exp->tmp), ERROR);
	free_and_null((void **)&exp->newest);
	exp->newest = ft_strdup(tmp);
	if (!exp->newest)
		return (free_and_null((void **)&tmp),
			free_and_null((void **)&exp->tmp), ERROR);
	free_and_null((void **)&tmp);
	free_expansion(exp->newest, ms->exp, ms);
	free_and_null((void **)&exp->tmp);
	return (SUCCESS);
}

char	*expand_heredoc(char *str, t_env *envp, t_mini **mini)
{
	t_expand	exp;
	t_mini		*ms;

	exp.i = 0;
	ms = *mini;
	exp.newest = ft_strdup("");
	free_expansion(exp.newest, ms->exp, *mini);
	while (str[exp.i])
	{
		norm_helper(str, &exp, ms);
		if ((ft_is_dollar(str[exp.i])) && (str[(exp.i) + 1] && (str[(exp.i)
						+ 1] != '$')))
		{
			if (is_dollar_hd(&exp, str, ms, envp) != ERROR)
				continue ;
			else
				return (NULL);
		}
		norm_helper_two(str, &exp, ms);
	}
	free_and_null((void **)&str);
	return (exp.newest);
}

void	do_while(int fd, char *end, bool expand, t_mini **mini)
{
	char	*line;

	signal_handler(4, *mini);
	while (1)
	{
		if (g_sig)
			break ;
		line = readline("> ");
		if (!line)
			return ;
		if (ft_strcmp(line, end) == 0)
		{
			free_and_null((void **)&line);
			return ;
		}
		if (expand == true)
			line = expand_heredoc(line, (*mini)->env, mini);
		ft_putendl_fd(line, fd);
		free_and_null((void **)&line);
	}
}

int	heredoc(t_parse *node, char *end, bool expand, t_mini **mini)
{
	int		fd;
	char	*name;

	name = get_unique_heredoc_name(mini);
	if (!name)
		return (ERROR);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	do_while(fd, end, expand, mini);
	close(fd);
	if (node->infd != 0)
		close(node->infd);
	node->infd = open(name, O_RDONLY);
	free_and_null((void **)&name);
	if (node->infd < 0)
		return (ERROR);
	return (SUCCESS);
}
