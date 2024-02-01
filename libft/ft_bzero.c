/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:18:29 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:00:57 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
/*

int	main(void)
{
	unsigned char s[11] = "Hello World";
	size_t n = 3;
	ft_bzero(s, n);
	printf("the new string %s \n", s);
	bzero(s, n);
	printf("bzero is  %s \n", s);
	return (0);
}

The  bzero()  function  erases  the data in the n bytes of the memory starting
at the location
pointed to by s, by writing zeros (bytes containing '\0') to that area.
*/
