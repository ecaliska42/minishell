/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/05 12:56:19 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_functions(char *s, t_env *environment, t_parse *com, t_env **envp)
{
	t_mini count;
	parse_temp(s, &com, &count);
	pathfinder(&com, &environment);
	execute(&com, &count, envp);
	return 0;
}

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
			break;
		new_node->name = get_till(envp[i], '=');
		new_node->values = ft_split(get_after(envp[i], '='), ':');
		new_node->next = NULL;
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
	t_env	*environment;
	t_parse	*commands;
  t_shell shell;
	// char *line;

	ft_bzero(&shell, sizeof(t_shell));
	printf("Welcome to minishell!\n");
	ft_readline(&shell);

	(void) av;
	if (ac != 1)
		return(write(2, "PLEASE EXECUTE MINISHELL WITH ./minishell only!\n", 49));
	if (!envp || !envp[0])
		return (write(2, "No envp no Minishell :'(\n", 26));
	environment = NULL;
	commands = NULL;

	copy_environment(envp, &environment);
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