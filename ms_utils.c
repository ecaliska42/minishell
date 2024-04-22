/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:22:20 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/22 14:52:38 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libraries/minishell.h"

char	*get_till(char *str, char character)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == character)
			break ;
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
			break ;
		}
		i++;
	}
	ret = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	j = 0;
	while (str[i])
	{
		ret[j] = str[i];
		j++;
		i++;
	}
	return (ret);
}

int	return_write(char *str, int ret)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (ret);
}
