#include "../../includes/minishell.h"

void    buildins_hub(t_data *data)
{
    if (ft_strstr(&data->cmd->cmd[0], "cd"))
        ft_cd(data);
    else if (ft_strstr(&data->cmd->cmd[0], "echo"))
        ft_echo(&data->cmd->cmd);
    else if (ft_strstr(&data->cmd->cmd[0], "exit"))
        ft_exit(data);
    else if (ft_strstr(&data->cmd->cmd[0], "env"))
        ft_env(data->env);
    else if (ft_strstr(&data->cmd->cmd[0], "pwd"))
        ft_pwd(0);
}