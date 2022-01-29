/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:09:23 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 16:09:24 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void    exe(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     pid;

    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    pid = fork();
    if (pid == 0)
        execve(path, cmd, env);
    wait(0);
}

int ft_execve(t_data *data, char **env)
{
    t_lst  *tmp;
    int     i;

    tmp = data->cmd;
    while (tmp)
    {
//        if (tmp->flag == 1)
//            exe_pipe(tmp);
//        else if (tmp->flag == 2)
//            exe_redirect(tmp);
//        else if (tmp->flag == 0)
        exe(tmp, env);
        tmp = tmp->next;
    }
}