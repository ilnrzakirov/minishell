/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:20 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 16:36:10 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env *init_env(t_data *data, char **env)
{
    int     i;
    char    *j;
    t_env   *tmp;

    data->env = malloc(sizeof(t_env));
    tmp = data->env;
    i = 0;
    while (env[i])
    {
        j = ft_strchr(env[i], '=');
        tmp->key = ft_substr(env[i], 0, ft_strichr(env[i], '=') + 1);
        tmp->value = ft_substr((j + 1), 0, ft_strlen(j) - 1);
        tmp->next = malloc(sizeof(t_env));
        tmp = tmp->next;
        i++;
    }
    tmp = NULL;
    data->std_in = dup(0);
    data->std_out = dup(1);
    return (data->env);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;
    t_env   *envp;

    envp = init_env(&data, env);
    g_data = &data;
	while (1)
	{
		line = readline("\033[1;31mminishell->\033[0m ");
		parser(line, &data);
	}
	return (0);
}
