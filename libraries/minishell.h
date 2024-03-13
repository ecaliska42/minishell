/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:22:56 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/13 20:27:50 by mesenyur         ###   ########.fr       */
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

# include "../libft/libft.h"
# include "parsing.h"

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
# include <stdbool.h>

typedef struct t_commands
{
	char	**command;
	struct t_commands	*next;
} t_command;

typedef struct t_env
{
	char	*name;
	char	**values;
	struct t_env	*next;
}	t_env;

typedef struct parse
{
	char	*check;		//TODO THE STRING OF THE PATH CHECKED WITH ACCESS IF EXECUTABLE WITH THE FIRST COMMAND ATTATCHED [FOR EXAMPLE /usr/bin/LS] HAVE TO DO
	char	**command;	//TODO THE 2D ARRAY FOR EXECVE ENDING WITH NULL HAVE TO DO
	long	infd;		//TODO THE RETURN VALUE OF OPEN
	long	outfd;		//TODO THE RETURN VALUE OF OPEN
	struct	parse *next;
}	t_parse;

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
	int		pipecount;
}	t_exe;


/*
	*BUILDINS
*/
int	ft_echo(char *str);
int	ft_cd(t_env **lst, char *s);
int	ft_env(t_env **envp);
int	ft_unset(void);
int	ft_pwd(void);
int	ft_export(t_env **lst);
int	ft_exit(void);

/*
	*PARSE_TEMPORARY
*/

/*
	*EXECUTION
*/
int	execute(t_parse **comm, int pipecount, t_env **envp);

/*
	*MS_UTILS
*/
char	*get_till(char *str, char character);
char	*get_after(char *str, char character);


void	printf_double(char **str);
void	printf_tripple(char ***str);

/*
	*BUILDIN_CHECK.C
*/
bool	is_buildin(char **command);
int		execute_buildin(char **s, t_env **envp);
int		parrent_buildin(char *s, t_env **envp);
bool	is_parrent_buildin(char *s);

void	*dup_for_no_pipes(t_parse *comm);
void	*dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i);
void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils);

int ft_readline(t_shell *shell, t_parse *command, t_env *envp);
int	prepare_for_execution(t_parse **command, t_exe *count, t_token **tokens, t_env **envp);

void	heredoc(t_parse *node, char *end);

//extras
void	expand_variable(t_shell *shell, t_env *env);


#endif