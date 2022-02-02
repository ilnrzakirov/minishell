/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlee <bcarlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:26:21 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/01 11:26:23 by bcarlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int len(char **arg)
{
    int i;

    i = 0;
    while (arg[i])
        i++;
    return (i);
}

int ft_echo(char **arg)
{
    int i;
    int n;

    i = 1;
    n = 0;
    if (len(arg) > 1) {
        while (arg[i])
        {
            if (arg[i] && ft_strnstr(arg[i], "-n", 2) == 0)
            {
                n = 1;
                i++;
            }
            while (arg[i])
            {
                ft_putstr_fd(arg[i], 1);
                if (arg[i + 1] && arg[i][0] != '\0')
                    write(1, " ", 1);
                i++;
            }
        }
    }
    if (n == 0)
        write (1, "\n", 1);
    exit(EXIT_SUCCESS);
}

int ft_env(t_env *e)
{
    t_env   *env;

    env = e;
    while(env)
    {
        write(1, env->key, ft_strlen(env->key));
        write(1, env->value, ft_strlen(env->value));
        write(1, "\n", 1);
        env= env->next;
    }
    exit(EXIT_SUCCESS);
}
