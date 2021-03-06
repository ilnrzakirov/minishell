/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_hub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:40:05 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 14:49:04 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	buildins_hub_parent(t_lst *cmd)
{
	if (g_data ->check_path == 1)
		return (0);
	if (ft_strstr(cmd->cmd[0], "export"))
	{
		ft_export(cmd, 0);
		return (1);
	}
	else if (ft_strstr(cmd->cmd[0], "unset"))
	{
		ft_unset(cmd);
		return (1);
	}
	else if (ft_strstr(cmd->cmd[0], "cd"))
	{
		ft_cd(cmd);
		return (1);
	}
	else if (ft_strstr(cmd->cmd[0], "exit"))
		ft_exit(cmd, g_data);
	return (0);
}

void	buildins_hub(t_lst *cmd, t_data *data)
{
	if (g_data ->check_path == 1)
		exit(EXIT_FAILURE);
	if (ft_strstr(cmd->cmd[0], "cd"))
		ft_cd(cmd);
	else if (ft_strstr(cmd->cmd[0], "echo"))
		ft_echo(cmd->cmd);
	else if (ft_strstr(cmd->cmd[0], "env"))
		ft_env(data->env);
	else if (ft_strstr(cmd->cmd[0], "pwd"))
	{
		if (ft_pwd(0))
			exit(EXIT_SUCCESS);
		else
			exit(EXIT_FAILURE);
	}
}
