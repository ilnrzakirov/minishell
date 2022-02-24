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

int ft_echo(char **arg)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!ft_strcmp(arg[1], "-n"))
	{
		i++;
		j++;
	}
	while (arg[++i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!j)
		write(STDOUT_FILENO, "\n", 1);
	g_data->exit_code = 0;
	exit (0);
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
    exit(0);
}
