/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:07:20 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/11 17:08:13 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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
		// exit(131);
		g_sig = 131;
	}
	// g_sig = signal_num;

	// printf("signal_num: %d\n", g_sig);
}

// non interactiuve -> \n

// heredoc -> ioctl

void non_interactive(int signal_num)
{
	(void)signal_num;
	ft_putstr_fd("\n", 1);
}

void	signal_handler(int mode)//, t_mini *ms)
{
	if (mode == 1)
	{
		signal(SIGINT, catch_signals);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, catch_signals);
	}
	else if (mode == 3)
	{
		signal(SIGINT, non_interactive);
		signal(SIGQUIT, non_interactive);
	}
}
