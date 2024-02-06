/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 18:21:04 by ecaliska          #+#    #+#             */
/*   Updated: 2024/02/06 17:23:55 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char *directory;

	directory = malloc(FILENAME_MAX);
	if (getcwd(directory, FILENAME_MAX) == NULL)
	{
		perror("");
		free(directory);
		return 1;
	}
	printf("%s\n", directory);
	free(directory);
	return 0;
}