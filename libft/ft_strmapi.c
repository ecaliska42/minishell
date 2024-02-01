/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:25:18 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/14 20:50:27 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = (f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*

char ft_write(unsigned int i, char s)
{
	s -= 32;
	i++;
	//write(1, &s[i], 1);
	return (s);
}

int main()
{
	char s [] = "was geht mit dir alter";
	char *str = ft_strmapi(s, ft_write);
	printf("%s", str);
}
*/