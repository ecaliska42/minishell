/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:52 by ecaliska          #+#    #+#             */
/*   Updated: 2023/10/28 19:57:36 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*mal;
	size_t	res;

	if (nmemb == 0 || size == 0)
	{
		mal = (char *)malloc(0);
		if (!mal)
			return (NULL);
		mal[0] = 0;
		return (mal);
	}
	res = size * nmemb;
	if (res != 0 && res / nmemb != size)
		return (NULL);
	mal = (char *)malloc (nmemb * size);
	if (!mal)
	{
		free (mal);
		return (NULL);
	}
	ft_bzero (mal, (nmemb * size));
	return (mal);
}
/*
int main(void)
{
	size_t nmemb = 5;
	size_t size = 4;
	ft_calloc(nmemb, size);
}
*/