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

void    exe_redirect(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     pid;
    int     fd;

    env = get_env(lst->data);
    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    if (lst->redirect_type == 1)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (lst->redirect_type == 2)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (lst->cmd)
    {
        pid = fork();
        if (pid == 0)
        {
            init_signal_chaild(lst->data);
            dup2(fd, 1);
            execve(path, cmd, env);
            close(fd);
        }
    }
}

void    exe(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     pid;

    env = get_env(lst->data);
    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    pid = fork();
    if (pid == 0) {
        init_signal_chaild(lst->data);
        execve(path, cmd, env);
    }
    close(STDIN_FILENO);
    dup2(lst->data->std_in, 0);
    wait(0);
}

void    exe_pipe(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     fd[2];
    int     pid;

    env = get_env(lst->data);
    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        init_signal_chaild(lst->data);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execve(path, cmd, env);
    }
    wait(0);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    close(fd[1]);
}

void    get_data(t_lst *lst, char **env)
{
    int fd;

    fd = open(lst->filename, O_RDONLY);
    dup2(fd , 0);
    close(fd);
}

int ft_execve(t_data *data, char **env)
{
    t_lst  *tmp;
    int     i;

    tmp = data->cmd;
    if (!tmp)
        return (1);
    while (tmp)
    {
        if (tmp->flag == 1)
            exe_pipe(tmp, env);
        else if (tmp->flag == 3)
            get_data(tmp, env);
        else if (tmp->flag == 2)
            exe_redirect(tmp, env);
        else if (tmp->flag == 0)
            exe(tmp, env);
        tmp = tmp->next;
    }
    return (0);
}