/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:13 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:43:42 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	i = ft_strlen(s);
	ch = c;
	s += i;
	while (i >= 0)
	{
		if (*s == ch)
			return ((char *)s);
		s--;
		i--;
	}
	if (c == 0)
		return ((char *)s);
	return (NULL);
}
/*
int main(void)
{
	const char s[] = "Hellto Wortld";
	int c = 'z';
	ft_strrchr(s, c);
	printf("this is the ft_ funct.: %s\n", ft_strrchr(s, c));
	printf("this is the orig. funct.: %s\n", strrchr(s, c));
	return 0;
}
*/

/*The strrchr() function returns a pointer to the last  occurrence
of the character c in the string s.*/