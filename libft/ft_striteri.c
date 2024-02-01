/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:25:21 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:44:13 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		(f)(i, &s[i]);
		i++;
	}
}
/*
void ft_write(unsigned int i, char *s)
{
	s[i] -= 32;
	write(1, &s[i], 1);
	//toupper(s[i]);
}

int main()
{
	char s [] = "hello";
	ft_striteri(s, ft_write);
}
*/
/*
Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.
*/