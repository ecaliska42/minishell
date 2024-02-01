/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:54 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:45:45 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	i = 0;
	str = (const char *) s;
	while (i < n)
	{
		if (str[i] == (char)c)
		{
			return ((void *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
/*
int main(void)
{
	const char s[] = "Hello Wortld.";
	int c = 'l';
	size_t n = 2;
	printf("this is the ft_function: %s\n", (char *)ft_memchr(&s,c,n));
	printf("this is the original function: %s\n", (char *)memchr(&s,c,n));
}*/