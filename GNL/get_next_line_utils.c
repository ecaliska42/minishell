/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:29:03 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/08 14:36:19 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (free ((char *)s1), NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free((char *)s1);
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_gnl_strdup(const char *s)
{
	char	*dup;
	int		i;
	int		len;

	len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
	{
		free ((char *) s);
		return (NULL);
	}
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*new_str(char *str)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	i = ft_strlen(str);
	while (str[j] != '\n')
		j++;
	if (str[j] == '\n')
		j += 1;
	temp = (char *)malloc((sizeof(char) * (i - j + 1)));
	if (!temp)
		return (free ((char *)str), NULL);
	i = 0;
	while (str[j])
	{
		temp[i] = str[j];
		j++;
		i++;
	}
	temp[i] = '\0';
	free ((char *)str);
	return (temp);
}
