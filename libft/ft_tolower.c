/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 21:05:35 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int main (void)
{
	int c = 'h';
	printf("This is ft_ function: %c\n", ft_tolower(c));
	printf("This is original function: %c\n",tolower(c));
	return 0;
}
*/
/*If  c is an uppercase letter, tolower() returns its lowercase
equivalent,
if a lowercase representation exists
in the current locale.  Otherwise, it returns c.*/