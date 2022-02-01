/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:53:42 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/01 13:53:43 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void clear_struct(t_data *data)
{
    while(data->cmd)
    {
        if (data->cmd->cmd)
            free(data->cmd->cmd);
        if (data->cmd->filename)
            free(data->cmd->filename);
        data->cmd = data->cmd->next;
    }
    data->cmd = NULL;
}

char *ft_find_path(char *str, int i)
{
    char    *cmd;
    char    *tmp;
    char    **path;

    cmd = ft_strjoin("/", str);
    path = ft_split(getenv("PATH="), ':');
    while(path[i])
    {
        tmp = ft_strjoin(path[i], cmd);
        if (access(tmp, F_OK))
        {
            free(tmp);
            tmp = NULL;
        }
        else
        {
            free(cmd);
            clear_arr(path);
            return (tmp);
        }
        i++;
    }
    clear_arr(path);
    free(cmd);
    return (NULL);
}