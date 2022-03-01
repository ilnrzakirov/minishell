/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:40:21 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 16:01:00 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sigquit(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_data->exit_code = 130;
}

static void	ft_signal_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
	g_data->exit_code = 131;
}

void	sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
	}
}

void	init_signal_child(void)
{
	signal(SIGQUIT, ft_signal_quit);
	signal(SIGINT, sigquit);
}

void	init_signal_h(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_func);
}
