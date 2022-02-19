#include "../../includes/minishell.h"

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