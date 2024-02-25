/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_word_after_char.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 13:36:06 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/25 15:15:05 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "minishell.h"

bool	is_whitspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

char	*get_the_word(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (is_whitspace(*str) == true && str[i])
		str++;
	if (str[i] == 0)
		return (NULL);
	while (is_whitspace(str[i]) == false && str[i])
		i++;
	ret = malloc(i + 1);
	if (!ret)
	{
		write(2, "malloc fail in get_the_word\n", 29);
		return (NULL);
	}
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	*get_first_word_after_char(char *str, char c)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (str[i])
	{
		if (str[i] == c)
		{
			s = get_the_word(&str[++i]);
			break ;
		}
		i++;
	}
	return (s);
}

/*
int	main(int ac, char **av)
{
	char	*s;

	(void)ac;
	s = get_first_word_after_char(av[1], *av[2]);
	if (!s)
		return (printf("NOTHING FOUND AFTER CHARACTER\n"));
	printf("return of the function is \n%s\n", s);
	free(s);
	return (0);
}
*/
