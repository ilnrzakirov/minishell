/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:20 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 13:04:31 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exe.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	if (argc > 1)
		return (print_error("No such file or directory\n", 2));
	while (1)
	{
		line = readline("\033[1;31mminishell->\033[0m ");
		data.cmd->cmd = line;
        data.cmd->flag = 1;
		ft_execve(&data);
	}
	return (0);
}
