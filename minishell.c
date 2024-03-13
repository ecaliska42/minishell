/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/13 13:45:36 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "./libraries/parsing.h"

int	copy_environment(char **envp, t_env **lst)
{//TODO PROTECTION
	int	i;
	t_env *new_node;
	t_env	*tail;

	i = 0;
	while(envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			break;//TODO CORRECT MALLOC PROTECTION!!
		new_node->name = get_till(envp[i], '=');
		if (!new_node->name)
			break;//TODO CORRECT MALLOC PROTECTION!!
		new_node->values = ft_split(get_after(envp[i], '='), ':');
		if (!new_node->values)
			break;//TODO CORRECT MALLOC PROTECTION!!
		new_node->next = NULL;
		if (ft_strncmp(new_node->name, "SHLVL", 5) == 0)
			new_node->values[0] = ft_itoa(ft_atoi(new_node->values[0]) + 1);
		if (*lst == NULL)
			*lst = new_node;
		else
			tail->next = new_node;
		tail = new_node;
		i++;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*environment;
	t_parse	*commands;
	t_shell shell;
	// char *line;

	environment = NULL;
	copy_environment(envp, &environment);
	commands = NULL;
	ft_bzero(&shell, sizeof(t_shell));
	printf("Welcome to minishell!\n");
	ft_readline(&shell, commands, environment);

	//TODO swrite some buildins tomorrow
	// while ((line = readline("shell > ")))
	// {
	// 	add_history(line);
	// 	parse_functions(line, environment, commands, &environment);
	// 	continue;
	// }
	// if(!line)
	// 	return (write(2, "ERROR ON READLINE\n", 19));
	// free(line);
	return 0;
}

//TODO MAKE READLINE PRINT THE CORRECT HOSTNAME

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