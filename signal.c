/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:07:20 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/29 20:04:31 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libraries/minishell.h"
#include "libraries/parsing.h"
#include <readline/readline.h>
#include <signal.h>
#include <sys/ioctl.h>

void	catch_signals(int signal_num)
{
	if (signal_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = SIGINT;
	}
	else if (signal_num == SIGQUIT)
	{
		ft_putstr_fd("Quit: (core dumped)\n", 1);
		g_sig = SIGQUIT;
	}
}

void	non_interactive(int signal_num)
{
	g_sig = signal_num;
	ft_putstr_fd("\n", 1);
}

void	signal_handler_heredoc(int signal_num)
{
	g_sig = signal_num;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(0, TIOCSTI, "\n");
}

void	signal_handler(int mode, t_mini *ms)
{
	(void)ms;
	if (mode == READLINE)
	{
		signal(SIGINT, catch_signals);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, catch_signals);
	}
	else if (mode == NON_INTERACTIVE)
	{
		signal(SIGINT, non_interactive);
		signal(SIGQUIT, non_interactive);
	}
	else if (mode == HERDOC)
	{
		signal(SIGINT, signal_handler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}
