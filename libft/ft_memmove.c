/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:07:11 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:01:24 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*a;
	char	*p;

	a = (char *)dest;
	p = (char *)src;
	if (!dest && !src)
		return (dest);
	if (dest <= src)
		while (n-- > 0)
			*a++ = *p++;
	else
	{
		a += n;
		p += n;
		while (n-- > 0)
			*--a = *--p;
	}
	return (dest);
}
/*
int main(void)
{
	//unsigned char dest[] ="AAAAAAAAA";
	//unsigned char src[] ="BBBBBBBBBBBB";
	unsigned char dest2[] ="AAAAAAAAA";
	unsigned char src2[] ="BBBBBBBBBBBB";
	size_t n = 20;
	//ft_memmove(&dest, src, n);
	memmove(&dest2, src2, n);
	//printf("This is the destination %s\n", dest);
	printf("This is the destination %s\n", dest2);
}
*/
/*
The  memmove()  function  copies n bytes from memory area src to memory
area dest. The memory areas may overlap: copying takes place as though
the bytes in src are first
copied into a temporary  array that does not overlap src or dest,
and the bytes are then copied from the tempo‐
rary array to dest.*/