/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_hub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:40:05 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/20 09:40:07 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    buildins_hub_parent(t_lst *cmd)
{
	if (ft_strstr(cmd->cmd[0], "export")) {
		ft_export(cmd, 0);
		return (1);
	}
	return (0);
}

void    buildins_hub(t_lst *cmd, t_data *data)
{
    if (ft_strstr(cmd->cmd[0], "cd"))
        ft_cd(cmd);
    else if (ft_strstr(cmd->cmd[0], "echo"))
        ft_echo(cmd->cmd);
    else if (ft_strstr(cmd->cmd[0], "exit"))
        ft_exit(cmd ,data);
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