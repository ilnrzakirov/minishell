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
void    exe(t_list *lst)
{
    char    **cmd;
    char    *path;

    cmd = ft_split(lst->cmd, " ");
    path =
}

int ft_execve(t_data *data)
{
    t_list  *tmp;
    int     i;

    tmp = data->cmd;
    while (tmp)
    {
        if (tmp->flag == 1)
            exe_pipe(tmp);
        else if (tmp->flag == 2)
            exe_redirect(tmp);
        else if (tmp->flag == 0)
            exe(tmp);
        tmp = rmp->next;
    }
}