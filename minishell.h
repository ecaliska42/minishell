/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:22:56 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/08 11:38:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\033[0;31m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# include "libft/libft.h"

// GNU Readline library
# include <readline/readline.h>     //readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/history.h>

// Standard input/output library
# include <stdio.h>     //printf
// Memory management library
# include <stdlib.h>    //malloc, free, getenv
// Unix standard library
# include <unistd.h>    //write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit
// Directory handling library
# include <sys/types.h> //opendir, readdir, closedir
// Error handling library
# include <sys/wait.h> //strerror, perror
// Terminal I/O library
# include <signal.h>    //isatty, ttyname, ttyslot, ioctl
# include <fcntl.h>
// Terminfo library
# include <ncurses.h>   //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
// Terminal control library
# include <termios.h>   //tcsetattr, tcgetattr

typedef struct t_commands
{
	char	**command;
	struct t_commands	*next;
} t_command;

typedef struct t_files
{
	char	*infile;
	char	*outfile;
}	t_file;

typedef struct t_env
{
	char	*name;
	char	**values;
	struct t_env	*next;
}	t_env;

/*
	*BUILDINS
*/
int	ft_echo(char *str);
int	ft_cd(void);
int	ft_env(t_env *envp);
int	ft_unset(void);
int	ft_pwd(void);		//TODO finsihed
int	ft_export(void);
int	ft_exit(void);

#endif