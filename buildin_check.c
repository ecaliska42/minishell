/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 17:03:55 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/24 16:34:37 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "libft/libft.h"
#include "libraries/parsing.h"
#include <ncurses.h>

int	lonely_buildin(t_parse *parse, t_env **envp, t_token **token)
{
	int orig_stdout = dup(STDOUT_FILENO);
	int orig_stdin = dup(STDIN_FILENO);
	if (parse->outfile)
	{
		parse->outfd = open(parse->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (parse->outfd == -1)
			perror("OUTFD ERROR1:");
		dup2(parse->outfd, 1);
		close(parse->outfd);
	}
	if (parse->infile)
	{
		parse->infd = open(parse->infile, O_RDONLY);
		if (parse->infd == -1)
			perror("INFD ERROR1:");
		dup2(parse->infd, 0);
		close(parse->infd);
	}
	execute_buildin(&parse, envp, token, 0);
	if (dup2(orig_stdin, STDIN_FILENO) == -1)
		perror("dup2 error (execute.c) : ");
	if (close (orig_stdin) == -1)
		perror("close error (execute.c) : ");
	if (dup2(orig_stdout, STDOUT_FILENO) == -1)
		perror("dup2 error (execute.c) : ");
	if (close (orig_stdout) == -1)
		perror("close error (execute.c) : ");
	return (SUCCESS);
}

bool	is_buildin(char **command)
{
	char	*s;

	if (!command)
		return false;
	s = command[0];
	if (ft_strcmp("echo", s) == 0)
		return true;
	else if (ft_strcmp("pwd", s) == 0)
		return true;
	else if (ft_strcmp("env", s) == 0)
		return true;
	else if (ft_strcmp("cd", s) == 0)
		return true;
	else if (ft_strcmp("exit", s) == 0)
		return true;
	else if (ft_strcmp("unset", s) == 0)
		return true;
	return false;
}

int	execute_buildin(t_parse **parse, t_env **envp, t_token **head, int pipecount)
{
	char	*s;

	s = (*parse)->command[0];
	// ft_putendl_fd("IN EXEC BUILDIN", 2);
	// ft_putendl_fd(s, 2);
	if (!s)
		return 0;
	if (ft_strcmp("echo", s) == 0)
		ft_echo(head, parse);
	else if (ft_strcmp("pwd", s) == 0)
		ft_pwd();
	else if (ft_strcmp("env", s) == 0)
		ft_env(envp);
	else if (ft_strcmp("cd", s) == 0)//?NOT IN CHILD
		ft_cd(envp, s);
	else if (ft_strcmp("exit", s) == 0)
		ft_exit(parse);
	else if (ft_strcmp("unset", s) == 0 && pipecount == 0)
		ft_unset(head, parse, envp);
	return (0);
}
