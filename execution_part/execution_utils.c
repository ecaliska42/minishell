/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:13:38 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/27 13:11:50 by mesenyur         ###   ########.fr       */
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

char	**change_envp(t_env **envp, t_mini *mini)
{
	int		size;
	char	**new_envp;
	char	*temp;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = *envp;
	size = t_env_size(envp);
	new_envp = ft_calloc(size + 1, sizeof(char *));
	if (!new_envp)
	{
		mini->exit_status = 1;
		check_malloc_exit(envp, mini);
	}
	while (i < size)
	{
		temp = ft_strjoin(tmp->name, "=");
		check_malloc_exit(temp, mini);
		new_envp[i] = ft_strjoin(temp, tmp->values);
		check_malloc_exit(new_envp[i++], mini);
		free_and_null((void **)&temp);
		tmp = tmp->next;
	}
	return (new_envp);
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
