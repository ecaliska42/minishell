/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:01 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:55:37 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*dest;
	char	*source;
	size_t	len;
	size_t	destlen;

	dest = dst;
	source = (char *)src;
	len = size;
	while (len-- != 0 && *dest != '\0')
		dest++;
	destlen = dest - dst;
	len = size - destlen;
	if (len == 0)
		return (destlen + ft_strlen(source));
	while (*source != '\0')
	{
		if (len != 1)
		{
			*dest++ = *source;
			len--;
		}
		source++;
	}
	*dest = '\0';
	return (destlen + (source - src));
}

/*

int main(void)
{
	char dst[] = "This is";
	const char src[] = "a potentially long string";
	size_t size = 16;
	printf("this is the dst string: %s\n",dst);
	//printf("this is the ft_function: %zu\n",ft_strlcat(dst,src,size));
	//printf("this is the dst string with ft: %s\n",dst);
	printf("this is the original function: %zu\n",strlcat(dst,src,size));
	printf("this is the dst new string: %s\n",dst);
}
*/

/*
int main()
{
	char first[] = "This is ";
	char last[] = "a potentially long string";
	int r;
	int size = 16;
	char buffer[size];

	strcpy(buffer,first);
	r = strlcat(buffer,last,size);

	puts(buffer);
	printf("Value returned: %d\n",r);
	if( r > size )
		puts("String truncated");
	else
		puts("String was fully copied");

	return(0);
}
*/

/*
The strlcat() function concatenates strings respectively.
They are designed to be safer, more consistent, and less
error prone replacements for strncpy(3) and strncat(3).
Unlike those functions, strlcat() takes the full size of
the buffer (not just the length) and guarantees to
NUL-terminate the result (as long as size is larger than 0
or, in the case of strlcat(), as long as there is at least
one byte free in dst).  Note that a byte for the NUL should
be included in size.  Also note that strlcpy() and strlcat()
only operate on true “C” strings. This means that for strlcat()
both src and dst must be NUL-terminated.

The strlcat() function appends the NUL-terminated string src
 to the end of dst.
It will append at most size - ft_strlen(dst) - 1 bytes,
NUL-terminating the result.
*/