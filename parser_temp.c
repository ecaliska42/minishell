/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/15 15:30:07 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

t_env	*get_path(t_env **envi)
{
	t_env	*temp;

	temp = *envi;
	while (ft_strncmp(temp->name, "PATH", 4) != 0)
		temp = temp -> next;
	if (!temp)
		return NULL;
	return temp;
}

char	*get_access(char *str, t_env **envi)
{//TODO maybe change the if statement if the str is already a whole path so my char **command contains the command only
	t_env	*path;
	int		i;
	char	*temp;
	char	**path_values;

	i = 0;
	if (access(str, X_OK | F_OK) == 0)
		return (str);
	path = get_path(envi);
	if (!path)
		return (NULL);
	path_values = ft_split(path->values, ':');
	while (path_values[i])
	{
		temp = ft_strdup("");
		temp = ft_strjoin(path_values[i], "/");
		temp = ft_strjoin(temp, str);
		if (access(temp, X_OK | F_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (str);
}



void	get_check(t_parse **head, t_env **envi)//TODO get the char *check with char **command
{
	t_parse *node; //char **command should already be set up
	int	i = 0;

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
		node = node -> next;
		i++;
	}
}

//execve ("/usr/bin/ls", {ls; -l; NULL}, ENVP)

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

int	array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return 0;
	while (array[i])
		i++;
	return (i);
}

char	**create_command(char *str, char **cmd)
{
	int	size = array_size(cmd);
	if (ft_strlen(str) == 0)
		return (cmd);
	int	i = 0;
	char **ret = ft_calloc (sizeof(char *), size + 2);
	if (!ret)
	{
		ft_putstr_fd("malloc error create command\n", 2);
		exit(1);
	}
	while (i < size)
	{
		ret[i] = ft_strdup(cmd[i]);
		//free(cmd[i]);
		i++;
	}
	ret[i] = ft_strdup(str);
	//free(str);
	return (ret);
}

void free_parsing_node(t_parse **head)
{
	t_parse	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (*head)
	{
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
					//tmp->command[i] = NULL;
				}
				i++;
			}
		}
		if (tmp->command)
		{
			free(tmp->command);
			tmp->command = NULL;
		}
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = *head;
	}
}

int	prepare_for_execution(t_parse **command, t_exe *count, t_token **tokens, t_env **envp)
{
	t_parse *node;
	t_token	*tmp;

	tmp = *tokens;
	count->pipecount = 0;
	node = malloc(sizeof(t_parse));
	if (!node)
	{
		ft_putstr_fd("malloc\n", 2);
		exit(1);
	}
	ft_bzero(node, sizeof(*node));
	while (tmp)
	{
		if (tmp -> type == INPUT && ft_strlen(tmp->str) > 0)//TODO <
		{
			node->infd = open(tmp->str, O_RDONLY);
			if (node->infd == -1)
				perror("INFD ERROR1:");
		}
		if (tmp -> type == OUTPUT && ft_strlen(tmp->str) > 0)//TODO > CHANGE NAME AFTER MERGE
		{
			node->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (node->outfd == -1)
				perror("OUTFD ERROR1: ");
		}
		if (tmp -> type == APPEND && ft_strlen(tmp->str) > 0)//TODO >>
		{
			node->outfd = open(tmp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (node->outfd == -1)
				perror("OUTFD ERROR2:");
		}
		if (tmp -> type == HEREDOC && ft_strlen(tmp->str) > 0)//TODO <<
		{
			heredoc(node, tmp->str);
			//return (0); //TODO WRITE A SEPPERATE FUNCTION FOR HEREDOC
		}
		if (tmp -> type == RANDOM)
		{
			node -> command = create_command(tmp->str, node->command); //TODO PREPARE IT FOR THE EXECVE
		}
		if (tmp -> type == PIPE)
		{
			count->pipecount++;
			add_back(command, node);
			node = malloc(sizeof(t_parse));
			ft_bzero(node, sizeof(*node));
		}
		tmp = tmp ->next;
	}
	add_back(command, node);
	get_check(command, envp);
	execute(command, count->pipecount, envp);
	free_parsing_node(command);
	return 0;
}
