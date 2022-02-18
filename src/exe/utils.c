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

int ft_env_lstsize(t_env *e)
{
    int	    count;
    t_env   *env;

    env = e;
    count = 0;
    while (env)
    {
        env = env->next;
        count++;
    }
    return (count);
}

char **get_env(t_data *data)
{
    int     i;
    t_env   *env;
    char    **res;

    env = data->env;
    i = 0;
    res = malloc(sizeof(char*) * ft_env_lstsize(env) + 1);
    while(env)
    {
        res[i++] = ft_strjoin(ft_strdup(env->key), env->value);
        env = env->next;
    }
    return (res);
}

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

    cmd = ft_strjoin(ft_strdup("/"), str);
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