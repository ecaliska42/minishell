/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/19 18:37:55 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "./libraries/parsing.h"
#include "libft/libft.h"
#include <stdio.h>

void print_env(t_env **envp)
{
	t_env *tmp = *envp;

	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->values);
		tmp = tmp->next;
	}
}

char	*get_pwd(void)
{
	char *path;

	path = malloc(FILENAME_MAX);
	if (!path)
		return (NULL);
	if (getcwd(path, FILENAME_MAX) == NULL)
	{
		perror("");
		free(path);
		return (NULL);
	}
	return (path);
}

// int  create_if_no_envp(t_env **envp)
// {
// 	printf("HERE\n");
// 	t_env *node = malloc(sizeof(t_env));
// 	if (!node)
// 		return (ERROR);
// 	t_env *node2 = malloc(sizeof(t_env));
// 	if (!node2)
// 		return (free(node), ERROR);
// 	t_env *node3 = malloc(sizeof(t_env));
// 	if (!node3)
// 		return (free(node), free(node2), ERROR);
// 	node->name = ft_strdup("PWD");
// 	node->values = get_pwd();
// 	node2->name = ft_strdup("SHLVL");
// 	node2->values = ft_itoa(1);
// 	node3->name = ft_strdup("_");
// 	node3->values = ft_strdup("/usr/bin/env");
// 	node->next = node2;
// 	node2->next = node3;
// 	node3->next = NULL;
// 	*envp = node;
// 	return (SUCCESS);
// }

char	**create_if_no_envp(char **envp)
{
	envp = ft_calloc (4, sizeof(char **));
	envp[0] = ft_strdup("PWD=/home/ecaliska/42/Common_Core/circle_three/minishell");
	envp[1] = ft_strdup("SHLVL=1");
	envp[2] = ft_strdup("_=/usr/bin/env");
	return (envp);
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*environment;
	t_parse	*commands;
	t_shell shell;
	//char *line;

	if (envp == NULL || envp[0] == NULL)
		envp = create_if_no_envp(envp);
	if (copy_environment(envp, &environment) == ERROR)
		return (1);
	commands = NULL;
	ft_bzero(&shell, sizeof(t_shell));
	printf("Welcome to minishell!\n");
	ft_readline(&shell, commands, environment);
	// while ((line = readline("shell > ")))
	// {
	// 	add_history(line);
	// 	parse_functions(line, environment, commands, &environment);
	// 	continue;
	// }
	// if(!line)
	// 	return (write(2, "ERROR ON READLINE\n", 19));
	// free(line);
	free_environment(&environment);
	return 0;
}


//TODO BUILDINS: echo with -n || cd with only relative or absolout path
//TODO BUILDINS: export with no options || unset with no options || env with no options or arguments
//TODO BUILDINS: exit with no options

//TODO DONE: pwd with no options ||

//TODO MAKE THE PROMPT PRINT THE CORRECT HOSTNAME

/*
	* can you give me a description of these function and its return values if they have one
*/

/*
	* ALLOWED FUNCTIONS:
	* add_history
	* access
	* wait
	* waitpid
	* wait3
	* wait4
	* signal
	* sigaction
	* sigemptyset
	* sigaddset
	* kill
	* getcwd
	* chdir
	* stat
	* lstat
	* fstat
	* unlink
	* execve
	* dup
	* dup2
	* opendir
	* readdir
	* closedir
	* isatty
	* ttyname
	* ttyslot
	* ioctl
	* getenv
	* tcsetattr
	* tcgetattr
	* tgetent
	* tgetflag
	* tgetnum
	* tgetstr
	* tgoto
	* tputs
	! readline
	! rl_clear_history
	! rl_on_new_line
	! rl_replace_line
	! rl_redisplay
	! printf
	! malloc
	! free
	! write
	! open
	! read
	! close
	! fork
	! exit
	! pipe
	! perror
	! strerror
*/