/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 20:09:16 by ecaliska          #+#    #+#             */
/*   Updated: 2023/09/22 17:15:19 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == c && s[i])
		{
			i++;
		}
		else
		{
			word++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (word);
}

static char	**freeing(char **str, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static char	*duplic(const char *s, int c)
{
	char	*dup;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	dup = malloc(sizeof(char) * i + 1);
	if (!dup)
		return (NULL);
	while (count < i)
	{
		dup[count] = s[count];
		count++;
	}
	dup[count] = '\0';
	return (dup);
}

static char	**while_loop(int *j, char const *s, char c, char **str)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		str[*j] = duplic(&s[i], c);
		if (!str[*j])
			return (freeing(str, *j));
		i += ft_strlen(str[(*j)++]);
	}
	str[*j] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**str;

	j = 0;
	if (!s)
		return (NULL);
	str = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!str)
		return (NULL);
	str = while_loop(&j, s, c, str);
	if (!str)
		return (NULL);
	if (j == 0)
	{
		free(str);
		str = NULL;
		str = malloc(sizeof(char *));
		if (!str)
			return (NULL);
		str[0] = NULL;
		return (str);
	}
	return (str);
}

/*int    main(void)
{
	int i = 0;
	
	//char    *tab = "\0aa\0bbb";
	char **out = ft_split(NULL, '\0');
	if (!out)
		return 1;
	while (out[i])
	{
		printf("%s\n", out[i]);
		free(out[i]);
		i++;
	}
	free(out);
	return (0);
}*/