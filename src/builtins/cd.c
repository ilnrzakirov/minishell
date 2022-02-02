/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:13:49 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/01 14:13:49 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_prev_dir(char **old, t_data *data)
{
    char    *new;

    if (!old)
    {
        ft_putendl_fd("cd: OLDPWD not set", 2);
        data->exit_code = 1;
        return (EXIT_FAILURE);
    }
    else
    {
        new = ft_pwd(1);
        chdir(*old);
        free(*old);
        *old = ft_strdup(new);
        free(new);
        data->exit_code = 0;
    }
    return (EXIT_SUCCESS);

}

int put_error(t_data *data)
{
    ft_putstr_fd("cd: ", 2);
    ft_putstr_fd(&data->cmd->cmd[1], 2);
    ft_putstr_fd(": ", 2);
    perror(NULL);
    data->exit_code = 1;
    return (EXIT_FAILURE);
}

int get_dir(char **old, t_data *data)
{
    if (old)
        free(*old);
    *old = ft_pwd(1);
    if (chdir(&data->cmd->cmd[1]))
        return (put_error(data));
    return (EXIT_SUCCESS);
}


int ft_cd(t_data *data)
{
    static char *old;

    if (data->cmd->flag == 1)
        return (EXIT_SUCCESS);
    if (!data->cmd->cmd[1] || !ft_strcmp(&data->cmd->cmd[1], "~"))
    {
        if (old)
            free(old);
        old = ft_pwd(1);
        chdir(getenv("HOME"));
    }
    else if (!ft_strcmp(&data->cmd->cmd[1], "-")) {
        if (get_prev_dir(&old, data))
            return (EXIT_FAILURE);
        ft_pwd(0);
    }
    else
        if (get_dir(&old, data))
            return (EXIT_FAILURE);
    data->exit_code = 0;
    return (EXIT_SUCCESS);
}
