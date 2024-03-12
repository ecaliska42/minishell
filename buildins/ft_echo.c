/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:20:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/12 18:47:58 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int ft_echo(char *str) //echo "hello"
{
	int i = 0;
	int j = 0;
	//int	x = 0;
	int	space = 0;
	while (str[i] == ' ')
		i++;
	char *s = malloc(ft_strlen(str) - i + 1);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			if (space == 0)
			{
				s[j++] = str[i];
				space = 1;
			}
			i++;
			continue;
		}
		s[j++] = str[i++];
		space = 0;
	}
	s[j] = '\0';
	printf("%s\n", s);
	free(s);
	return 0;
}
