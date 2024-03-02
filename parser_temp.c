/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/02 19:15:05 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void pathfinder(t_parse **comm, t_env **envi)
{
	t_env *tmp = *envi;
	t_parse *tmp2 = *comm;
	int x = 0;
	char *temp;

	while(ft_strncmp(tmp->name, "PATH", 4) != 0)
		tmp = tmp->next;
//environment struct should now be in the PATH struckt there are multiple values split
	while (tmp2)
	{
		x = 0;
		while (tmp->values[x])
		{
			if (access(tmp2->command[0], X_OK | F_OK) == 0)
			{
				tmp2->check = tmp2->command[0];
				tmp2->command[0] = ft_strrchr(tmp2->command[0], '/');
				tmp2->command[0]++;
				break;
			}
			else
			{
				temp = ft_strdup("");
				temp = ft_strjoin(tmp->values[x], "/");
				temp = ft_strjoin(temp, tmp2->command[0]);
				if (access(temp, X_OK | F_OK) == 0)
				{
					tmp2->check = temp;
					break;
				}
			}
			free(temp);
			x++;
		}
		tmp2 = tmp2 -> next;
	}
	tmp = *envi;
	tmp2 = *comm;
}

char	*remove_after_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			s[i] = '\0';
			break ;
		}
		i++;
	}
	return s;
}

char **parse_temp(char *s, t_parse **commands, t_mini *count)
{
	int i = 0;
	count->pipecount = count_in_line(s, '|');
	char **temp = ft_split(s, '|');
	t_parse *node;
	while (temp[i])
	{
		node = malloc(sizeof(t_parse));
		node->infile = get_first_word_after_char(temp[i], '<'); //TODO done by parsing part by MELIH
		if (node->infile)
		{
			node->infd = open(node->infile, O_RDONLY);
			if (node->infd == -1)
				perror("");
		}
		node->outfile = get_first_word_after_char(temp[i], '>'); //TODO done by parsing part by MELIH
		if (node->outfile && node->infd != -1)
		{
			node->outfd = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (node->outfd == -1)
				perror("");
		}
		else
			node->outfd = -1;
		if (node->infile)
		{
			if (temp[i][0] == ' ')
				temp[i] = &temp[i][1];
			if (temp[i][1] == ' ')
				temp[i] = &temp[i][2];
			temp[i] = &temp[i][ft_strlen(node->infile) + 1];
		}
		node->command = ft_split(remove_after_char(temp[i], '>'), ' ');
		node->next = NULL;
		add_back(commands, node);
		i++;
	}
	return NULL;
}

/*
	TODO ARGUMENTS FOR PREPARE_FOR_EXECUTION ARE T_PARSE **COMMAND;;T_EXE FOR THE PIPECOUNT
	TODO pipes are type 0
	TODO count all pipes for correct redirection and put them in t_exe in pipecount
	TODO in the struct t_parse open all infiles and outfiles with node->infile & node->outfile
	TODO get the command (RANDOM) type 5 and put them together in a two dimensional array ending with NULL for execve in execution
	TODO cat < infile | > outfile wc -l
	TODO if type is 0 (PIPE) add the whole node to the command linked list
	TODO 
	TODO 
*/

int	prepare_for_execution()
{
	return 0;
}