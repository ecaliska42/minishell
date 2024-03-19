/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:58 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/15 21:59:46 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return (NULL);
}

/*
int main(void)
{
	const char s[] = "Hellto World";
	int c = 't';
	printf("this is the ft_ funct.: %s\n", ft_strchr(s, c));
	printf("this is the orig. funct.: %s\n", strchr(s, c));
	return 0;
}
The strchr() function returns a pointer to the first occurrence
of the character c in the string s.*/