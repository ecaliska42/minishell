/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesenyur <mesenyur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:07:20 by mesenyur          #+#    #+#             */
/*   Updated: 2024/04/04 15:05:51 by mesenyur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libraries/minishell.h"

void    interactive_handler(int signal_num)
{
    if (signal_num == SIGINT)
    {
        ft_putstr_fd("\n", 1);
        
    }
}

//non interactiuve -> \n

//heredoc -> ioctl

void signal_handler(int mode)
{
    if(mode == 1)
    {
        signal(SIGINT, interactive_handler);
        signal(SIGQUIT, SIG_IGN);
    }
}


