/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/16 19:12:41 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"
#include "./libraries/parsing.h"

void print_env(t_env **envp)
{
	t_env *tmp = *envp;

	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->values);
		tmp = tmp->next;
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env	*environment;
	t_parse	*commands;
	t_shell shell;
	//char *line;

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