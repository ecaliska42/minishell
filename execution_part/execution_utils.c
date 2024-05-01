/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:38 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/30 15:04:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_fds(int **fds)
{
	int	i;

	i = 0;
	if (!fds || !fds[i])
		return ;
	while (fds[i])
	{
		free_and_null((void **)&fds[i]);
		i++;
	}
	free_and_null((void **)&fds);
}

void	free_until_envp(char **envp, int i)
{
	while (i >= 0)
	{
		free_and_null((void **)&envp[i]);
		i--;
	}
	free_and_null((void **)&envp);
}

char	**change_envp(t_env **envp, t_mini *mini)
{
	t_change_envp_vars	vars;

	vars.i = 0;
	vars.tmp = *envp;
	vars.size = t_env_size(envp);
	vars.new_envp = ft_calloc(vars.size + 1, sizeof(char *));
	if (!vars.new_envp)
		return (NULL);
	while (vars.i < vars.size)
	{
		vars.temp = ft_strjoin(vars.tmp->name, "=");
		check_malloc_exit(vars.temp, mini);
		vars.new_envp[vars.i] = ft_strjoin(vars.temp, vars.tmp->values);
		free_and_null((void **)&vars.temp);
		if (!vars.new_envp[vars.i])
		{
			free_until_envp(vars.new_envp, vars.i);
			return (NULL);
		}
		vars.tmp = vars.tmp->next;
		vars.i++;
	}
	return (vars.new_envp);
}

int	malloc_ex_struct(t_exe *ex_struct)
{
	ex_struct->id = ft_calloc((ex_struct->pipecount + 1), sizeof(pid_t));
	if (!ex_struct->id)
	{
		perror("ex_struct.id malloc error (execute.c) :");
		return (ERROR);
	}
	ex_struct->fd = ft_calloc((ex_struct->pipecount + 2), sizeof(int *));
	if (!ex_struct->fd)
	{
		free_and_null((void **)&ex_struct->id);
		perror("ex_struct.fd malloc error (execute.c) :");
		return (ERROR);
	}
	return (SUCCESS);
}

int	create_pipes(t_exe *ex_struct)
{
	int	i;

	i = 0;
	while (i < ex_struct->pipecount)
	{
		ex_struct->fd[i] = malloc(sizeof(int) * 2);
		if (!ex_struct->fd[i])
		{
			perror("ex_struct.fd[i] malloc error (execute.c) : ");
			ft_putnbr_fd(i, 2);
			return (ERROR);
		}
		if (pipe(ex_struct->fd[i]) == -1)
		{
			perror("pipe error (execute.c) : ");
			ft_putnbr_fd(i, 2);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
