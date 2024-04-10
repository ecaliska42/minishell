/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/10 18:03:53 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

t_env	*get_path(t_env **envi)
{
	t_env	*temp;

	temp = *envi;
	while(temp)
	{
		if (ft_strncmp(temp->name, "PATH", 4) == 0)
			break;
		temp = temp -> next;
	}
	if (!temp)
		return NULL;
	return temp;
}

char	*get_access(char *str, t_env **envi)
{//TODO maybe change the if statement if the str is already a whole path so my char **command contains the command only
	t_env	*path;
	int		i;
	char	*temp;
	char	*temp2;
	char	**path_values;

	i = 0;
	if (access(str, X_OK | F_OK) == 0)
		return (str);
	path = get_path(envi);
	if (!path)
		return (NULL);
	path_values = ft_split(path->values, ':');
	if (!path_values)
	{
		ft_putstr_fd("malloc error get_access\n", 2);
		return (NULL);
	}
	while (path_values[i]) // possible leaks
	{
		temp = ft_strdup("");
		temp = ft_strjoin(path_values[i], "/");
		temp2 = ft_strjoin(temp, str);
		free(temp);
		temp = NULL;
		if (access(temp2, X_OK | F_OK) == 0)
			return (temp2);
		i++;
		free (temp2);
	}
	return (str);
}

static int	get_check(t_parse **head, t_env **envi)//TODO get the char *check with char **command
{
	t_parse *node; //char **command should already be set up

	node = *head;
	while (node)
	{
		// printf("node command is %s\n", node->command[0]);
		if (node->command == NULL)
		{
			node = node -> next;
			continue;
		}
		node->check = get_access(node->command[0], envi);
		if (!node->check)
			return (ERROR);
		node = node -> next;
	}
	return (SUCCESS);
}

static void add_back(t_parse **com, t_parse *node)
{
	t_parse	*temp;

	if (*com == NULL)
		*com = node;
	else
	{
		temp = *com;
		while (temp -> next != NULL)
		{
			temp = temp -> next;
		}
		temp -> next = node;
	}
	temp = *com;
}

/*
	TODO ARGUMENTS FOR PREPARE_FOR_EXECUTION ARE T_PARSE **COMMAND;;T_EXE FOR THE PIPECOUNT;;T_TOKEN
	TODO pipes are type 0
	TODO count all pipes for correct redirection and put them in t_exe in pipecount
	TODO in the struct t_parse open all infiles and outfiles with node->infile & node->outfile
	TODO get the command (RANDOM) type 5 and put them together in a two dimensional array ending with NULL for execve in execution
	TODO cat < infile | > outfile wc -l
	TODO if type is 0 (PIPE) add the whole node to the command linked list
*/

char	**create_command(char *str, char **cmd)
{
	int	size = array_size(cmd);
	// if (ft_strlen(str) == 0)
	// 	return (cmd);
	int	i = 0;
	char **ret = ft_calloc (size + 2, sizeof(char *));
	if (!ret)
	{
		ft_putstr_fd("malloc error create command\n", 2);
		exit(1);
	}
	while (i < size)
	{
		ret[i] = ft_strdup(cmd[i]);
		i++;
	}
	while (size)
	{
		free(cmd[size]);
		cmd[size] = NULL;
		size--;
	}
	ret[i] = ft_strdup(str);
	// free(str);
	// str = NULL;
	return (ret);
}

void free_parsing_node(t_parse **head)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	while (*head != NULL)
	{
		tmp = *head;
		*head = (*head) -> next;
		// if (tmp->check)
		// {
		// 	free(tmp->check);
		// 	tmp->check = NULL;
		// }
		if (tmp->command)
		{
			i = 0;
			while(tmp->command[i])
			{
				if (tmp->command[i])
				{
					free(tmp->command[i]);
					tmp->command[i] = NULL;
				}
				i++;
			}
			free(tmp->command);
			tmp->command = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
	}
}

int	prepare_for_execution(t_mini **shell)//(t_parse **command, t_exe *count, t_token **tokens, t_env **envp)
{
	t_parse *node;
	t_token	*tmp;

	t_mini *mini = *shell;
	tmp = mini->shell.tokens;
	mini->exe.pipecount = 0;
	node = malloc(sizeof(t_parse));
	if (!node)
	{
		ft_putendl_fd("malloc", 2);
		exit(1);
	}
	ft_bzero(node, sizeof(*node));
	while (tmp)
	{
		if (tmp -> type == INPUT && ft_strlen(tmp->str) > 0)
		{
			// node->infile = tmp->str;
			// node->infile_type = INPUT;
			node->infd = open(tmp->str, O_RDONLY);
			if (node->infd == -1)
				perror("");
		}
		else if (tmp -> type == OUTPUT && ft_strlen(tmp->str) > 0 && node->execute == EXECUTE)
		{
			// node->outfile = tmp->str;
			// node->outfile_type = OUTPUT;
			node->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (node->outfd == -1)
			{
				perror("");
				node->execute = IGNORE;
			}
		}
		else if (tmp -> type == APPEND && ft_strlen(tmp->str) > 0 && node->execute == EXECUTE)
		{
			// node->outfile = tmp->str;
			// node->outfile_type = APPEND;
			node->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (node->outfd == -1)
			{
				perror("");
				node->execute = IGNORE;
			}
			// 	perror("OUTFD ERROR2:");
		}
		else if (tmp -> type == HEREDOC && ft_strlen(tmp->str) > 0)
		{
			// node->infile_type = HEREDOC;
			// node->infile = tmp->str;
			heredoc(node, tmp->str);
		}
		else if (tmp -> type == RANDOM)
			node->command = create_command(tmp->str, node->command);
		else if (tmp -> type == PIPE)
		{
			mini->exe.pipecount++;
			add_back(&mini->parse, node);
			node = malloc(sizeof(t_parse));
			if (!node)
			{
				ft_putendl_fd("malloc", 2);
				return (ERROR);
			}
			ft_bzero(node, sizeof(t_parse));
		}
		tmp = tmp ->next;
	}
	add_back(&mini->parse, node);
	get_check(&mini->parse, &mini->env);
	execute(&mini->parse, mini->exe.pipecount, &mini->env);
	free_parsing_node(&mini->parse);
	return (SUCCESS);
}
