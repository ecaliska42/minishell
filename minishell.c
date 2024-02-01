/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:40 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/01 02:44:43 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	get_hostname(char **line)
{
	int		i;
	int		j;
	char	*ret;

	if (!line)
		return NULL;
	j = 4;
	i = 0;
	while (ft_strncmp("USER", line[i], 4) != 0)
		i++;
	ret = malloc(ft_strlen(const char *str))
	while (line[j])
		
}

int main(int ac, char **av, char **envp)
{
	if (!envp)
		return 0;
	(void) av;
	(void) ac;
	char *line;
	char *host = 
	
	while ((line = readline("minishell >")))
	{
		
		continue;
	}
	//line = readline("minishell > ");
	if(!line)
		return (printf("error on readline\n"));
	printf("%s\n", line);
	free(line);
	return 0;
}

//TODO MAKE READLINE PRINT THE CORRECT HOSTNAME