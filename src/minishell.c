/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:14:20 by bcarlee           #+#    #+#             */
/*   Updated: 2022/03/02 15:49:06 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_shell_lvl(void)
{
	char	*key;
	char	*value;
	int		old_sh_lvl;

	key = ft_strdup("SHLVL=");
	value = get_value(key);
	old_sh_lvl = ft_atoi(value);
	old_sh_lvl++;
	free(value);
	value = ft_itoa(old_sh_lvl);
	replace_value_envp(key, value);
	if (!check_key("PATH="))
		g_data->check_path = 1;
}

void	init_env(char **env)
{
	int		i;
	char	*j;
	t_env	*tmp;

	g_data->env = malloc(sizeof(t_env));
	tmp = g_data->env;
	i = 0;
	while (env[i])
	{
		j = ft_strchr(env[i], '=');
		tmp->key = ft_substr(env[i], 0, ft_strichr(env[i], '=') + 1);
		if (ft_strlen(tmp->key) == 0)
			tmp->key = NULL;
		tmp->value = ft_substr((j + 1), 0, ft_strlen(j) - 1);
		if (ft_strlen(tmp->value) == 0)
			tmp->value = NULL;
		if (env[i + 1])
			tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		i++;
	}
	tmp = NULL;
	g_data->std_in = dup(0);
	g_data->std_out = dup(1);
}

void	main_part(int ac, char **av, char **env)
{
	(void)av;
	if (ac > 1)
		exit (print_error("No such file or directory\n", 2));
	init_env(env);
	g_data->exit_code = 0;
	g_data->check_path = 0;
	g_data->error = 0;
	replace_shell_lvl();
}

void	main_part2(void)
{
	dup2(g_data->std_in, 0);
	dup2(g_data->std_out, 1);
	init_signal_h();
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	data;

	g_data = &data;
	main_part(ac, av, env);
	while (1)
	{
		main_part2();
		line = readline("\033[1;31mminishell->\033[0m ");
		if (!line)
			check_line();
		if (line[0])
			add_history(line);
		if (!line[0])
		{
			free(line);
			continue ;
		}
		parser(line);
		ft_execve(g_data, env);
		clear_struct();
	}
	return (0);
}
