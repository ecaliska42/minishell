/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:06 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/29 19:12:03 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*little)
		return ((char *)big);
	if (len <= 0)
		return (NULL);
	if (len > ft_strlen (big))
		len = ft_strlen(big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] && big[i + j] == little[j]
			&& i + j < len && little[j])
			j++;
		if (little[j] == '\0')
			return ((char *)big + i);
		++i;
	}
	return (NULL);
}
/*
#include <stdio.h>
int main(void)
{

}
*/
/*
The strnstr() function locates the first occurrence of the null-termi‐
nated string little in the string big, where not more than len charac‐
ters are searched.  Characters that appear after a ‘\0’ character are
not searched.  Since the strnstr() function is a FreeBSD specific API,
it should only be used when portability is not a concern.*/
/*
x   If little is an empty string, big is returned;
o   if little occurs nowhere in big, NULL is returned
o   otherwise a pointer to the first character of the first occurrence
		of little is returned.
*/