/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:04 by ecaliska          #+#    #+#             */
/*   Updated: 2024/04/26 16:58:05 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_pwd(t_mini **mini)
{
	char	*directory;

	directory = malloc(FILENAME_MAX);
	if (!directory)
		return (ERROR);
	if (getcwd(directory, FILENAME_MAX) == NULL)
	{
		perror("ft_pwd");
		free_and_null((void **)&directory);
		return (ERROR);
	}
	printf("%s\n", directory);
	free_and_null((void **)&directory);
	(*mini)->exit_status = 0;
	return (SUCCESS);
}
