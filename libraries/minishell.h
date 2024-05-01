/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:22:56 by ecaliska          #+#    #+#             */
/*   Updated: 2024/05/01 15:33:10 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "parsing.h"
// GNU Readline library
# include <readline/readline.h>
# include <readline/history.h>
// Standard input/output library
# include <stdio.h>
// Memory management library
# include <stdlib.h>
// Unix standard library
# include <unistd.h>
// Directory handling library
# include <sys/types.h> //opendir, readdir, closedir
// Error handling library
# include <sys/wait.h> //strerror, perror
// Terminal I/O library
# include <signal.h>//isatty, ttyname, ttyslot, ioctl
# include <fcntl.h>
// Terminfo library
// # include <ncurses.h>   //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
// Terminal control library
// # include <termios.h>   //tcsetattr, tcgetattr
# include <stdbool.h>
# include <dirent.h>

extern int	g_sig;

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

typedef struct t_env
{
	char			*name;
	char			*values;
	struct t_env	*next;
}	t_env;

typedef struct parse
{
	char			*check;
	char			**command;
	int				infd;
	int				outfd;
	int				execute;
	bool			empty;
	struct parse	*next;
}	t_parse;

typedef struct s_exe
{
	pid_t	*id;
	int		**fd;
	int		pipecount;
}	t_exe;

typedef struct minishell
{
	t_exe		exe;
	t_parse		*parse;
	t_env		*env;
	t_shell		shell;
	t_expansion	*exp;
	int			exit_status;
}	t_mini;

/*
	*BUILDINS
*/

typedef struct t_export
{
	t_env	*envp;
	t_parse	*command;
	char	*before;
	char	*after;
	int		fail;
	int		i;
}	t_export;

typedef struct s_lonely_buildin
{
	int	orig_stdout;
	int	orig_stdin;
	int	flag;
}	t_lonely_buildin;

//EXPORT

//export.c

int		ft_export(t_env **lst, t_parse **node, t_mini **mini);
int		do_while_export(t_env *tmp, t_env **copy, t_env *node);
//export2.c

void	print_list(t_env **list);
void	ft_swap(t_env **node1, t_env **node2);
void	sort_list(t_env **head);
void	tenv_add_back(t_env ***lst, t_env *new_l);
int		copied_struct(t_env **src, t_env **copy);

//export3.c

void	free_list(t_env **head);
int		print_export(t_env *head);
int		env_addback(t_env **head, char *name, char *value);
int		get_before_after(char **before, char **after, char *s);
int		no_options(t_mini **mini, t_parse *command);

//export4.c

int		only_equal(t_mini **mini);
void	export_error(char *command, int *i, int *fail);
void	set_exit_status(int fail, t_mini **mini);
int		add_export(t_env *envp, char *before, char *after, char *command);
int		while_loop(t_export *expo, t_mini **mini);

typedef struct t_cd
{
	t_env	*home;
	t_env	*old;
	t_env	*current;
	t_parse	*parse;
}	t_cd;

typedef struct t_expand
{
	int		len;
	char	*tmp;
	int		i;
	char	*value;
	char	*newest;
	char	*name;
}	t_expand;

typedef struct s_change_envp_vars
{
	int		size;
	char	**new_envp;
	char	*temp;
	t_env	*tmp;
	int		i;
}	t_change_envp_vars;

//cd3.c
char	*remove_after_backslash(char *s);
int		dot_dot(t_env **old, t_env **current, t_mini *mini);
int		ch_dir_else(t_env **old, t_env **current, char *now);

//PARSER

t_parse	*is_pipe(t_mini **mini, t_parse **node);
int		is_file(t_token **tmp, t_parse ***node, t_mini **mini);
int		while_loop_parser(t_token *tmp, t_parse **node, t_mini *mini);
char	**create_command(char *str, char **cmd);
int		prepare_for_execution(t_mini **minishell);

t_env	*get_path(t_env **envi);
char	*do_while_access(char **path_values, char *str);
char	*get_access(char *str, t_env **envi, t_mini **mini);
int		get_check(t_mini **mini);
void	add_back(t_parse **com, t_parse *node);

void	free_parsing_node(t_parse **head);
int		is_input(char *name, t_parse ****node, t_mini **mini, t_token *tmp);
int		is_output(t_token *tmp, t_parse ****node);
int		is_append(t_token *tmp, t_parse ****node);
int		is_random(t_token *tmp, t_parse ***node);

char	*remove_after_schraegstrich(char *s);
int		dot(t_env **old);
int		only_cd(t_env *home, t_env **current, t_env **old);
int		go_back(t_env **old, t_env **current, t_mini **mini);

int		ft_cd(t_env **lst, t_parse **node, t_mini **mini);
int		ft_env(t_env **envp, t_mini **mini, t_parse **node);
int		ft_unset(t_parse **parsing, t_env **environment, t_mini **mini);
int		ft_pwd(t_mini **mini);
void	ft_exit(t_parse **node, t_mini **mini);
int		ft_echo(t_parse **node, t_mini **mini);

//*EXECUTION_PART

int		execute(t_mini **mini);

//*MS_UTILS

char	*get_till(char *str, char character);
char	*get_after(char *str, char character);

//*BOOLEANS

void	printf_double(char **str);
void	printf_tripple(char ***str);

// HEREDOC

void	norm_helper_two(char *str, t_expand *exp, t_mini *ms);
void	norm_helper(char *str, t_expand *exp, t_mini *ms);

	// *./SIZES

int		t_env_size(t_env **envp);
int		array_size(char **array);

	// *BUILDIN_CHECK.C

int		lonely_buildin(t_parse *parse, t_env **envp, t_mini **mini);
bool	is_buildin(char **command);
int		execute_buildin(t_parse **parse, t_env **env, int pc, t_mini **mini);
int		parrent_buildin(char *s, t_env **envp);
bool	is_parrent_buildin(char **s);

void	*close_filedescriptor(t_parse *comm, t_exe *ex_utils);

int		ft_readline(t_mini *mini);
int		heredoc(t_parse *node, char *end, bool expand, t_mini **mini);

int		copy_environment(char **envp, t_env **lst);
int		free_environment(t_env **lst);
void	*dup_for_no_pipes(t_parse *comm);
char	*skip_starting_ending_spaces(char *value);
char	*expand_heredoc(char *str, t_env *envp, t_mini **mini);
char	*replace_exit_code(char *str, char **new_str, int *i, t_mini *ms);
void	handle_quotes(t_token *token, char *str, t_mini *ms, t_expansion *exp);
bool	check_exp(char *str, int i);
int		do_expand(char *str, t_expansion *exp, t_mini *ms, t_token *token);

	// *EXECUTION

void	free_fds(int **fds);
char	**change_envp(t_env **envp, t_mini *mini);
int		malloc_ex_struct(t_exe *ex_struct);
int		create_pipes(t_exe *ex_struct);

//CHILD.C

int		child(t_parse *comm, int i, t_mini **mini, t_parse *head);

void	print_command_not_found(char **command, t_mini **mini);
void	print_correct_error_message(t_parse *comm, t_mini **mini);
int		dup_filedescriptor(t_parse *comm, t_exe *ex_utils, int i);
bool	is_only_numbers(char *s);
bool	is_alpha_numbers(char *s);
bool	first_character_is(char *s, char c);
int		return_write(char *str, int ret);

// SIGNALS

void	signal_handler(int mod, t_mini *ms);

// FREE

void	free_tokens(t_token **tokens);
void	check_malloc_exit(void *ptr, t_mini *mini);
void	free_expansion(void *ptr, t_expansion *exp, t_mini *ms);
void	free_mini_and_exit(t_mini **mini);
void	free_double(char **str);
void	free_exe(t_exe *ex_struct);
void	free_mini(t_mini **mini);
void	free_words(char **words);
t_token	*create_new_token(char *word, t_token *last);
void	get_rid_of_before_after(char **before, char **after);

// *EXPANSION

void	expansion(t_token *token, t_mini *ms);
t_token	*expand_variable(t_expansion exp, t_token *token, t_mini *ms);
t_token	*handle_closed(t_token *token, t_expansion *exp, t_mini *ms);
t_token	*handle_expansion(t_token *token, t_expansion *exp, t_mini *ms);
int		handle_heredoc_exp(t_token *token, t_expansion *exp, char *str,
			t_mini *ms);
char	*process_double_quotes(char *new_str, char *str, int *i, t_mini *ms);
char	*process_single_quotes(char *new_str, char *str, int *i);
char	*get_env_value(char *name, t_env *envp);
char	*add_char(char *str, char new_char);
t_env	*get_from_env(t_env **lst, char *s);
t_token	*split_value(char *str, char *value, t_token *token, t_expansion *exp);
char	*expand_heredoc_delimeter(char *new_str, char *str, int *i, t_mini *ms);
char	*handle_dollar_sign(char *new_str, char *str, int *i, t_mini *ms);

// TOKENIZING

char	*get_word(t_shell *shell, char *line, int *i, t_mini *ms);
int		not_pipe(t_shell *shell, t_token *last_token, int *i, t_mini *ms);
int		ft_strtok(t_shell *shell, int *i, t_mini *ms);
int		lexical_analyzer(t_shell *shell, t_mini *ms);
int		token_add(t_token **tokens, t_mini *ms);
t_token	*add_new_empty_token(t_shell *shell, t_mini *ms);


#endif