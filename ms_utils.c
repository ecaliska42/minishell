/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:22:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/22 15:50:37 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_in_line(char *s, char c)
{
	int	count;

	count = 0;
	while(*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return count;
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

/*
	*GHOST_FUNCTION
*/
char	*search_for(t_env *stack, char *str)
{
	while (stack->next)
	{
		if (ft_strncmp(stack->name, str, ft_strlen(str)) == 0)
			return (stack->values[0]);
		stack = stack ->next;
	}
	return (NULL);
}
/*
	*GHOST_FUNCITON FOR DEBUGGING ONLY
*/
void	ex(void)
{
	printf("%sHERE\n%s", RED, WHITE);
}

