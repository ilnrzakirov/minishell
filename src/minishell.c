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
    data->std_in = dup(0);
    data->std_out = dup(1);
    return (data->env);
}

void    init_history(t_data *data)
{
    t_history   *hs;

    hs = data->history;
    hs = (t_history *)malloc(sizeof (t_history));
}

void    add_history(t_data *data, char *str)
{
    char        *line;

    if (str) {
        line = ft_strdup(str);
        ft_link_lst_cr_front(&data->history, line);
    }
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
        dup2(data.std_in, 0);
        dup2(data.std_out, 1);
		line = readline("\033[1;31mminishell->\033[0m ");
		data.cmd->cmd = parser(line, &data);
		ft_execve(data);
	}
	return (0);
}
