/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:31:39 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:03:32 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (size <= 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int main(void)
{
	char dst[] = "AAAAAAAAAAAAAAAA";
	const char src[] = "BBBBBBBBBBB";
	size_t size = 5;
	size_t myc = ft_strlcpy(dst, src, size);
	size_t test = strlcpy(dst, src, size);
	printf("this is the code %zu\n", test);
	printf("this is the dest %s\n", dst);
	printf("this is the length %zu", myc);
	
}

*/
/*
The strlcpy() and strlcat() functions copy and concatenate strings
respectively. They are designed to be safer, more consistent,
and less error prone replacements for strncpy(3) and
strncat(3).  Unlike those functions, strlcpy() and strlcat()
take the full size of the buffer (not just the length) and guarantee
to NUL-terminate the result (as long as size is larger than 0
or, in the case of strlcat(), as long as there is at least one byte
free in dst).  Note that a byte for the NUL should be included in size.
Also note that strlcpy() and strlcat() only operate on true “C” strings.
This means that for strlcpy() src must be NUL-terminated and for strlcat()
both src and dst must be NUL-terminated.

The strlcpy() function copies up to size - 1 characters from the
NUL-terminated string src to dst, NUL-terminating the result.
*/