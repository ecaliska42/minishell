/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:04 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/20 15:24:27 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_pwd(void)
{
	//ft_putendl_fd("IN PWD", 2);
	char *directory;

	directory = malloc(FILENAME_MAX);
	if (!directory)
		return ERROR;
	if (getcwd(directory, FILENAME_MAX) == NULL)
	{
		perror("");
		free(directory);
		return ERROR;
	}
	printf("%s\n", directory);
	free(directory);
	return SUCCESS;
}
