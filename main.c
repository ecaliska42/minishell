/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <melih.senyurt@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:02:08 by mesenyur          #+#    #+#             */
/*   Updated: 2024/02/28 19:15:56 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void ft_init_shell(t_shell *shell)
// {
// 	shell = malloc(sizeof(t_shell));
// 	if (!shell)
// 	{
// 		ft_putstr_fd("Error: malloc failed\n", 2);
// 		exit(1);
// 	}
// 	ft_bzero(shell, sizeof(t_shell));
// 	printf("shell->quotes: %d\n", shell->quotes);
// }

int main(void)
{
	t_shell shell;

	ft_bzero(&shell, sizeof(t_shell));

	//ft_init_shell(&shell);
	printf("Welcome to minishell!\n");
	ft_readline(&shell);
	return (0);
}
