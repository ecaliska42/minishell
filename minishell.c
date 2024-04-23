/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/23 18:15:00 by ecaliska         ###   ########.fr       */
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

// char	*get_pwd(void)
// {
// 	char	*path;

// 	path = malloc(FILENAME_MAX);
// 	if (!path)
// 		return (NULL);
// 	if (getcwd(path, FILENAME_MAX) == NULL)
// 	{
// 		perror("getcwd() error: ");
// 		free(path);
// 		return (NULL);
// 	}
// 	return (path);
// }

char	**create_if_no_envp(char **envp)
{
	envp = ft_calloc(4, sizeof(char **));
	envp[0] = ft_strdup("PWD=/home/ecaliska/42/Common_Core");
	envp[0] = ft_strjoin(envp[0], "/circle_three/minishell");
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env");
	return (envp);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	if (envp == NULL || envp[0] == NULL)
		envp = create_if_no_envp(envp);
	if (copy_environment(envp, &mini.env) == ERROR)
		return (1);
	ft_bzero(&mini.shell, sizeof(t_shell));
	mini.parse = NULL;
	ft_readline(&mini);
	free_environment(&mini.env);
	return (0);
}
