/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/09 20:02:46 by ecaliska         ###   ########.fr       */
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
	int	i = 0;
	//int j = 0;
	t_env *tmp = *envi;
	t_parse *tmp2 = *comm;
	int x = 0;
	char *temp;
	while(ft_strncmp(tmp->name, "PATH", 4) != 0)
	{
		i++;
		tmp = tmp->next;
	}
//environment struct should now be in the PATH struckt there are multiple values split
	while (tmp2)
	{
		x = 0;
		// for(int i = 0; tmp->values[i]; i++)
		// 	printf("%s\n", tmp->values[x]);
		// exit(1);
		while (tmp->values[x])
		{
			usleep(5000);
			printf("%s\n", tmp->values[x]);
			temp = ft_strjoin(tmp->values[x], "/");
			temp = ft_strjoin(temp, tmp2->command[0]);
			if (access(temp, X_OK | F_OK))
				break;
			x++;
		}
		printf("temp is %s\n", temp);
		tmp2->check = temp;
		tmp2 = tmp2 -> next;
	}
	tmp = *envi;
	tmp2 = *comm;
}

char **parse_temp(char *s, t_parse **commands)
{
	// int	infile;
	// int	outfile;
	int i = 0;
	char **temp = ft_split(s, '|');
	t_parse *node;
	node = malloc(sizeof(t_parse));
	while (temp[i])
	{
		node->command = ft_split(temp[i], ' ');
		node->next = NULL;
		//printf("node is : %s\n", node->command[0]);
		add_back(commands, node);
		//ex();
		//printf("%s\n", temp[i]);
		i++;
	}
	return NULL;
}