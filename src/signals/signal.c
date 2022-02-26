/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:40:21 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/20 09:40:22 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void    sigint_func(int sig)
{
    if (sig == SIGINT)
    {
        rl_on_new_line();
        rl_redisplay();
        write(2, "  \n", 3);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    sigquit(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_data->exit_code = 130;
}

static	void	ft_signal_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
	g_data->exit_code = 131;
}

void    sigint_proc(int sig)
{
    if (sig == SIGINT)
    {
        write(2, "\n", 1);
    }
}

void    init_signal_chaild(t_data *data)
{
    signal(SIGQUIT, ft_signal_quit);
    signal(SIGINT, sigquit);
}

void    init_signal_h()
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sigint_func);
}