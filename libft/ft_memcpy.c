/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:13:56 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:01:43 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p;
	unsigned char	*a;

	if (n == 0)
		return (dest);
	if (!src && !dest)
		return (dest);
	p = (unsigned char *) src;
	a = (unsigned char *) dest;
	while (n--)
		a[n] = p[n];
	return (a);
}
/*
int	main(void)
{
//	char dest[] = "source";
//	char src[] = "notdestination";
	char dest2[] = "source";
	char src2[] = "notdestination";
	size_t n = 20;
//	ft_memcpy(&dest, &src, n);
	memcpy(dest2, src2, n);
//	printf("this is the destination %s\n", dest);
	printf("this is the destination %s\n", dest2);
	//printf("this is the orig. functi.: %s\n", memcpy(&dest, &src, n));
	return 0;
}
*/

/*
The  memcpy()  function  copies  n bytes from memory area src to memory
area dest.  The memory areas must not overlap.  Use memmove(3)  if  the
memory areas do overlap.
*/