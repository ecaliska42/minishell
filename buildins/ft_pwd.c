/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:04 by ecaliska          #+#    #+#             */
/*   Updated: 2024/03/14 11:51:12 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/minishell.h"

int	ft_pwd(void)
{
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
