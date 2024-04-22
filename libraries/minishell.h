/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:22:56 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 12:57:17 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int g_sig;

# define RED "\033[0;31m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

# define EXECUTE 0
# define IGNORE 1

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
# include <dirent.h>

typedef struct t_env
{
	char	*name;
	char	*values;
	//int		exit_status;
	struct t_env	*next;
}	t_env;

typedef struct parse
{
	char	*check;		//TODO THE STRING OF THE PATH CHECKED WITH ACCESS IF EXECUTABLE WITH THE FIRST COMMAND ATTATCHED [FOR EXAMPLE /usr/bin/LS] HAVE TO DO
	char	**command;	//TODO THE 2D ARRAY FOR EXECVE ENDING WITH NULL HAVE TO DO
	int		infd;		//TODO THE RETURN VALUE OF OPEN
	char	*infile;	//TODO THE FILE NAME FOR THE INFDFD
	int		infile_type;
	int		outfd;		//TODO THE RETURN VALUE OF OPEN
	char	*outfile;	//TODO THE FILE NAME FOR THE OUTFDFD
	int		outfile_type;
	int		execute;	//TODO THE FLAG FOR APPEND
	struct	parse *next;
}	t_parse;

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
	int		pipecount;
}	t_exe;

typedef struct minishell
{
	t_exe	exe;
	t_parse	*parse;
	t_env	*env;
	t_shell	shell;
	t_token	*tokens;
	int	exit_status;
}	t_mini;

/*
	*BUILDINS
*/
int		ft_cd(t_env **lst, t_parse **node, t_mini **mini);
int		ft_env(t_env **envp, t_mini **mini, t_parse **node);
int		ft_unset(t_parse **parsing, t_env **environment, t_mini **mini);
int		ft_pwd(t_mini **mini);
int		ft_export(t_env **lst, t_parse **node, t_mini **mini);
void	ft_exit(t_parse **node, t_mini **mini);
int		ft_echo(t_parse **node, t_mini **mini);

/*
	*EXECUTION_PART
*/
int	execute(t_mini **mini);//(t_parse **comm, int pipecount, t_env **envp)

/*
	*MS_UTILS
*/
char	*get_till(char *str, char character);
char	*get_after(char *str, char character);

/*
	*BOOLEANS
*/
void	printf_double(char **str);
void	printf_tripple(char ***str);


/*
	*./SIZES
*/
int	t_env_size(t_env **envp);
int	array_size(char **array);


/*
	*BUILDIN_CHECK.C
*/
int	lonely_buildin(t_parse *parse, t_env **envp, t_mini **mini);
bool	is_buildin(char **command);
int	execute_buildin(t_parse **parse, t_env **env, int pc, t_mini **mini);
int		parrent_buildin(char *s, t_env **envp);
bool	is_parrent_buildin(char **s);

void	*dup_for_no_pipes(t_parse *comm);
void	*dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i);
void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils);

int	ft_readline(t_mini *mini);//(t_shell *shell, t_parse *command, t_env *envp)//(t_mini *mini)//;
int	prepare_for_execution(t_mini **shell);//(t_parse **command, t_exe *count, t_token **tokens, t_env **envp)
void	heredoc(t_parse *node, char *end, bool expand, t_mini **mini);

/*
	*EXPANSION
*/

void	expansion(t_token *token, t_mini *ms);
t_token	*expand_variable(t_token *token, t_mini *ms);
char	*get_env_value(char *name, t_env *envp);
char 	*add_char(char *str, char new_char);
t_env	*get_from_env(t_env **lst, char *s);

int	copy_environment(char **envp, t_env **lst);
int	free_environment(t_env **lst);
void	*dup_for_no_pipes(t_parse *comm);
char	**change_envp(t_env **envp);
char *skip_starting_ending_spaces(char *value);
char	*expand_heredoc(char *str, t_env *envp, t_mini **mini);
char 	*replace_exit_code(char *str, char **ne, int *i, t_mini *ms);

/*
	*EXECUTION
*/
//EXECUTE.C

//EXECUTE_UTILS.C
void	free_fds(int **fds);
char	**change_envp(t_env **envp);
int		malloc_ex_struct(t_exe *ex_struct, int pipecount);
int		create_pipes(t_exe *ex_struct);
//CHILD.C
int	child(t_parse *comm, int i, t_mini **mini);



void	*dup_filedescriptors(t_parse *comm, t_exe *ex_utils, int i);
bool	is_only_numbers(char *s);
bool	is_alpha_numbers(char *s);
bool	first_character_is(char *s, char c);
int		return_write(char *str, int ret);



// SIGNALS

void	signal_handler(int mod, t_mini *ms);

// FREE

void 	one_function_to_free_them_all(t_mini *mini);

// EXPANSION

t_token *split_value(char *str, char *value, t_token *token);
char 	*replace_exit_code(char *str, char **new_str, int *i, t_mini *ms);
char	*add_char(char *str, char new_char);
char	*expand_heredoc_delimeter(char *new_str, char *str, int *i, t_mini *ms);
char	*process_double_quotes(char *new_str, char *str, int *i, t_mini *ms);
char	*process_single_quotes(char *new_str, char *str, int *i);
char 	*handle_dollar_sign(char *new_str, char *str, int *i, t_mini *ms);

/*
	*TEMPORARY debugging
*/



#endif