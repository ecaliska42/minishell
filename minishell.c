/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/02 17:45:48 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int main(int ac, char **av, char **envp)
{
	if (!envp)
		return 0;
	(void) av;
	(void) ac;
	char *line;
	
	while ((line = readline("minishell >")))
	{
		
		continue;
	}
	//line = readline("minishell > ");
	if(!line)
		return (printf("error on readline\n"));//todo stderr make
	printf("%s\n", line);
	free(line);
	return 0;
}

//TODO MAKE READLINE PRINT THE CORRECT HOSTNAME

//TODO BUILDINS: echo with -n || cd with only relative or absolout path || pwd with no options
//TODO BUILDINS: export with no options || unset with no options || env with no options or arguments
//TODO BUILDINS: exit with no options

/*
  * ALLOWED FUNCTIONS:
  * readline
  * rl_clear_history
  * rl_on_new_line
  * rl_replace_line
  * rl_redisplay
  * add_history
  * printf
  * malloc
  * free
  * write
  * access
  * open
  * read
  * close
  * fork
  * wait
  * waitpid
  * wait3
  * wait4
  * signal
  * sigaction
  * sigemptyset
  * sigaddset
  * kill
  * exit
  * getcwd
  * chdir
  * stat
  * lstat
  * fstat
  * unlink
  * execve
  * dup
  * dup2
  * pipe
  * opendir
  * readdir
  * closedir
  * strerror
  * perror
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
*/