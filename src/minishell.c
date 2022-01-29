/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:20 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 16:36:10 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	if (argc > 1)
		return (print_error("No such file or directory\n", 2));
	init_env(&data, env);
	while (1)
	{
		line = readline("\033[1;31mminishell->\033[0m ");
		data.cmd->cmd = parser(line, &data);
		ft_execve(data);
	}
	return (0);
}
