/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:17:25 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/29 14:40:31 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	only_equal(t_mini **mini)
{
	write(2, "export : '=': not a valid identifier\n", 38);
	(*mini)->exit_status = 1;
	return (ERROR);
}

void	export_error(char *command, int *i, int *fail)
{
	write(2, "export: '", 10);
	write(2, command, ft_strlen(command));
	write(2, "': not a valid identifier\n", 26);
	(*i)++;
	*fail = 1;
}

void	set_exit_status(int fail, t_mini **mini)
{
	if (fail == 1)
		(*mini)->exit_status = 1;
	else
		(*mini)->exit_status = 0;
}

int	add_export(t_env *envp, char *before, char *after, char *command)
{
	if (ft_strchr(command, '=') != NULL)
	{
		env_addback(&envp, before, after);
	}
	else
	{
		env_addback(&envp, before, NULL);
	}
	return (SUCCESS);
}

int	while_loop(t_export *ex, t_mini **mini)
{
	while (ex->command->command[ex->i])
	{
		if (get_before_after(&ex->before, &ex->after,
				ex->command->command[ex->i]) == ERROR)
			return (ERROR);
		if (ft_strchr(ex->command->command[ex->i], '=') != NULL
			&& ft_strlen(ex->command->command[ex->i]) == 1)
		{
			free_and_null((void **)&ex->before);
			free_and_null((void **)&ex->after);
			return (only_equal(mini));
		}
		if (ft_strlen(ex->before) == 0
			|| is_alpha_numbers(ex->before) == false)
		{
			export_error(ex->command->command[ex->i], &ex->i, &ex->fail);
			free_and_null((void **)&ex->before);
			free_and_null((void **)&ex->after);
			continue ;
		}
		add_export(ex->envp, ex->before, ex->after,
			ex->command->command[ex->i]);
		free_and_null((void **)&ex->before);
		free_and_null((void **)&ex->after);
		ex->i++;
	}
	return (SUCCESS);
}
