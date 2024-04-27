/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/27 13:31:07 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "./libraries/parsing.h"

int		g_sig = 0;

void	print_env(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->values);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	if (envp == NULL || envp[0] == NULL)
		return (1);
	if (copy_environment(envp, &mini.env) == ERROR)
		return (ERROR);
	ft_bzero(&mini.shell, sizeof(t_shell));
	ft_bzero(&mini.exe, sizeof(t_exe));
	mini.parse = NULL;
	ft_readline(&mini);
	free_environment(&mini.env);
	return (SUCCESS);
}
