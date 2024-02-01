/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:25:16 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:50:47 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	difference;
	int		start;
	char	*str;
	int		end;
	int		i;

	start = 0;
	i = 0;
	end = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (start < end && ft_strchr (set, s1[start]))
		start ++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	difference = end - start;
	str = (char *)malloc(sizeof(char) * difference + 1);
	if (!str)
		return (NULL);
	while (difference--)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}

/*
int main(void)
{
	char const s1 [] = "Hello WorldHel";
	char const set [] = "leH";
	printf("%s", ft_strtrim(s1, set));
}
*/
/*
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
*/