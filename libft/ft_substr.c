/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:25:14 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:43:44 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;

	i = 0;
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	subs = (char *)malloc(sizeof(char) * len + 1);
	if (!subs)
		return (NULL);
	while (i < len)
		subs[i++] = s[start++];
	subs[i] = '\0';
	return (subs);
}
/*
#include <stdio.h>

int main(void)
{
	char const s []= "1234567891011121314";
	unsigned int start = 5;
	size_t len = 8;
	printf("this is the function %s\n", ft_substr(s, start, len));
}
*/
/*
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.
*/