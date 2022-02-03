#include "../../includes/minishell.h"

int len_arr(char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
        i++;
    return (i);
}

int isdigit_char(char *str)
{
    int	i;

    i = -1;
    while (str[++i])
        if (str[i] > '9' || str[i] < '0')
            return (1);
    return (0);
}

void    ft_exit(t_data *data)
{
    if (data->cmd->flag != 0)
        return ;
    write(2, "exit", 4);
    if (len_arr(&data->cmd->cmd) > 1 && isdigit_char(&data->cmd->cmd[1]))
    {
        ft_putstr_fd("Bash: exit: ", 2);
        ft_putstr_fd(&data->cmd->cmd[1], 2);
        ft_putendl_fd(": numeric argument required", 2);
        data->exit_code = 255;
        exit(255);
    }
    else if (len_arr(&data->cmd->cmd) > 2 && !isdigit_char(&data->cmd->cmd[1]))
    {
        data->exit_code = 1;
        ft_putendl_fd("eBash: exit: too many arguments", 2);
    }
    else if (len_arr(&data->cmd->cmd) == 2 && ft_atoi(data->cmd->cmd))
        exit (ft_atoi(data->cmd->cmd));
    else
        exit (0);
}