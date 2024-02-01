/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:29 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/05 12:31:15 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char str[]="Hello World";
	int c = '+';
	size_t n = 6;
	printf("new string %s", (unsigned char *)ft_memset(str, c, n));
	return 0;
}
*/
/*
The  memset()  function  fills  the  first  n  bytes of the memory area
pointed to by s with the constant byte c.
*/
