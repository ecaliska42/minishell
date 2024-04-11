/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:38 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/11 13:19:45 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

void	free_fds(int **fds)
{
	int	i;

	i = 0;
	while (fds[i])
	{
		free(fds[i]);
		fds[i] = NULL;
		i++;
	}
	free(fds);
	fds = NULL;
}

char	**change_envp(t_env **envp)
{
	int		size;
	char	**new_envp;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *envp;
	size = t_env_size(envp);
	new_envp = ft_calloc(size + 1, sizeof(char *));
	if (!new_envp)
	{
		perror("new_envp malloc error (execute.c) :");
		exit (1);
	}
	// new_envp[size] = NULL;
	while (i < size)
	{
		new_envp[i] = ft_strjoin(tmp->name, "=");
		new_envp[i] = ft_strjoin(new_envp[i], tmp->values);
		i++;
		tmp = tmp->next;
	}
	return (new_envp);
}

int	malloc_ex_struct(t_exe *ex_struct, int pipecount)
{
	(void)pipecount;
	ex_struct->id = malloc((ex_struct->pipecount + 1) * sizeof(pid_t));
	if (!ex_struct->id)
	{
		perror("ex_struct.id malloc error (execute.c) :");
		return (ERROR);
	}
	ex_struct->fd = ft_calloc(ex_struct->pipecount + 2, sizeof(int *));
	if (!ex_struct->fd)
	{
		free(ex_struct->id);
		ex_struct->id = NULL;
		perror("ex_struct.fd malloc error (execute.c) :");
		return (ERROR);
	}
	// ex_struct->pipecount = pipecount;
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
	// ex_struct->fd[i] = NULL;
	return (SUCCESS);
}
