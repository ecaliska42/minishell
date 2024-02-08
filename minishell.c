/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/08 16:14:23 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	e(void)
{
	printf("%sHERE\n", RED);
}

/*
	TODO MAKE PROTECTIONS IF FUNCTIONS FAIL
*/
int	parse_functions(char *s, t_env *environment)
{
	if (ft_strncmp("echo ", s, 5) == 0)
		ft_echo(ft_strchr(s, ' '));
	if (ft_strncmp("pwd", s, 3) == 0)
		ft_pwd();
	if (ft_strncmp("env", s, 3) == 0)
		ft_env(environment);
	return 0;
}

char	*get_till(char *str, char character)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == character)
			break;
		i++;
	}
	ret = malloc(i + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*get_after(char *str, char character)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == character)
		{
			i++;
			break;
		}
		i++;
	}
	printf("after is %s\n", str);
	ret = malloc(ft_strlen(str) - i + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (str[i])
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int	copy_environment(char **envp, t_env **lst)
{
	int	i;
	t_env *new_node;
	t_env	*tail = NULL;

	i = 0;
	while(envp[i])
	{
		// printf("\nwhole envp for %d is %s\n", i, envp[i]);
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

char	*search_for(t_env *stack, char *str)
{
	int i;

	i = 0;
	while (stack->next)
	{
		if (ft_strncmp(stack->name, str, ft_strlen(str)) == 0)
		{
			return (stack->values[0]);
		}
		stack = stack ->next;
	}
	return (NULL);
}

int main(int ac, char **av, char **envp)
{
	if (!envp)
		return 0;
	(void) av;
	(void) ac;
	char *line;
	t_env	*environment = NULL;
	
	copy_environment(envp, &environment);
	//printf("%s@%s -> ", search_for(environment, "LOGNAME"), search_for(environment, "PWD"));
	while ((line = readline("shell > ")))
	{
		add_history(line);
		parse_functions(line, environment);
		//printf("%s@%s -> ", search_for(environment, "LOGNAME"), search_for(environment, "PWD"));
		//printf("%s\n", line);
		continue;
	}
	//line = readline("minishell > ");
	if(!line)
		return (write(2, "ERROR ON READLINE\n", 19));
	free(line);
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