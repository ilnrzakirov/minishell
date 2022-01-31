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

void    exe_redirect(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     pid;
    int     fd;

    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    if (lst->redirect_type == 1)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (lst->redirect_type == 2)
        fd = open(lst->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    pid = fork();
    if (pid == 0)
    {
        dup2(fd, 1);
        execve(path, cmd, env);
        close(fd);
    }
    wait(0);
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
    dup2(lst->data->std_in, 0);
    dup2(lst->data->std_out, 1);
}

void    exe_pipe(t_lst *lst, char **env)
{
    char    **cmd;
    char    *path;
    int     fd[2];
    int     pid;

    cmd = ft_split(lst->cmd, ' ');
    path = ft_find_path(cmd[0], 0);
    pipe(fd);
    pid = fork();
    // выполнить форк в дочке выполнить команду подменить дискриптеры в родителе подаждать
}

int ft_execve(t_data *data, char **env)
{
    t_lst  *tmp;
    int     i;

    tmp = data->cmd;
    while (tmp)
    {
        if (tmp->flag == 1)
            exe_pipe(tmp, env);
        else if (tmp->flag == 2)
            exe_redirect(tmp, env);
        else if (tmp->flag == 0)
            exe(tmp, env);
        tmp = tmp->next;
    }
    return (0);
}