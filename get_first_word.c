/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:26:14 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/26 16:23:20 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minishell.h"

static bool	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

char	*get_first_word(char *str)
{
	int		i;
	int		j;
	char	*ret;

	j = 0;
	i = 0;
	while (is_white_space(*str) == true)
		str++;
	while (is_white_space(str[i]) == false)
		i++;
	ret = malloc(i + 1);
	if (!ret)
	{
		write(2, "malloc failed in get_first_word\n", 30);
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

/*
int main(int ac, char **av)
{
	(void) ac;
	printf("first word is %s\n", first_word(av[1]));
	return (0);
}
*/
