/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:20 by bcarlee           #+#    #+#             */
/*   Updated: 2022/01/29 13:04:31 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_env(t_data *data, char **env)
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
}


int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;

	if (argc > 1)
		return (print_error("No such file or directory\n", 2));
	init_env(&data, env);
	while (1)
	{
		line = readline("\033[1;31mminishell->\033[0m ");
        data.cmd = malloc(sizeof (t_lst));
		data.cmd->cmd = line;
        data.cmd->flag = 1;
		ft_execve(&data, env);
	}
	return (0);
}
