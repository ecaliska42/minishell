/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:07:20 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/11 13:35:43 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"
#include <readline/readline.h>

int g_sig = 0;

void	catch_signals(int signal_num)
{
	if (signal_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 130;
	}
	else if (signal_num == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 1);
		g_sig = 131;
	}
	
}

// non interactiuve -> \n

// heredoc -> ioctl

void	signal_handler(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, catch_signals);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
	}
}
