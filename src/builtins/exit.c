/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:39:33 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 14:38:37 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_arr(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	isdigit_char(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] > '9' || str[i] < '0')
			return (1);
	return (0);
}

void	ft_exit(t_lst *cmd, t_data *data)
{
	if (cmd->flag != 0)
		return ;
	write(2, "exit\n", 5);
	if (len_arr(cmd->cmd) > 1 && isdigit_char(cmd->cmd[1]))
	{
		ft_putstr_fd("Bash: exit: ", 2);
		ft_putstr_fd(cmd->cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		data->exit_code = 255;
		exit (255);
	}
	else if (len_arr(cmd->cmd) > 2 && !isdigit_char(cmd->cmd[1]))
	{
		data->exit_code = 1;
		ft_putendl_fd("Bash: exit: too many arguments", 2);
		exit (1);
	}
	else if (len_arr(cmd->cmd) == 2 && ft_atoi(cmd->cmd[1]))
		exit (ft_atoi(cmd->cmd[1]));
	else
		exit (0);
}
