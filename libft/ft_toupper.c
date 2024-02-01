/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:32:20 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/15 13:03:39 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int main(void)
{
	int c = 'h';
	printf("this is ft_ function: %c\n", ft_toupper(c));
	printf("this is original function: %c\n", toupper(c));
	return 0;
}
*/
/*If  c is a lowercase letter, toupper() returns its uppercase
equivalent,
if an uppercase representation exists in the current locale. 
Otherwise,
it returns c.*/