/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:07:20 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/08 14:20:32 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void    catch_signals(int signal_num)
{
    if (signal_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        
    }
    else if (signal_num == SIGQUIT)
    {
        ft_putstr_fd("Quit: (core dumped)\n", 1);
    }
}

//non interactiuve -> \n

//heredoc -> ioctl

void signal_handler(int mode)
{
    if (mode == 1)
    {
        signal(SIGINT, catch_signals);
        signal(SIGQUIT, SIG_IGN);
    }
}


