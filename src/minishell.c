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

void	clear_env(void)
{
	t_env *en;

	if (g_data->env) {
		while (g_data->env) {
			en = g_data->env;
			if (g_data->env->key)
				free(g_data->env->key);
			if (g_data->env->value)
				free(g_data->env->value);
			g_data->env = g_data->env->next;
			free(en);
		}
		free(g_data->env);
	}
}

char	*get_value(char *key)
{
	t_env *temp;

	temp = g_data->env;
	while (temp && temp->key)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (0);
}

void	replace_shell_lvl(void){
	t_env	*temp;
	char 	*key;
	char 	*value;
	int 	old_sh_lvl;

	temp = g_data->env;
	key = ft_strdup("SHLVL=");
	value = get_value(key);
	old_sh_lvl = ft_atoi(value);
	old_sh_lvl++;
	free(value);
	value = ft_itoa(old_sh_lvl);
	replace_value_envp(key, value);
}

t_env *init_env(t_data *data, char **env)
{
	int     i;
	char    *j;
	t_env   *tmp;

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
	return (data->env);
}

int	main(int i, char **argv, char **env)
{
	char	*line;
	t_data	data;

	g_data = &data;
	if (i > 1)
		return (print_error("No such file or directory\n", 2));
    init_env(&data, env);
	replace_shell_lvl();
    data.exit_code = 0;
	while (1)
	{
		dup2(data.std_in, 0);
		dup2(data.std_out, 1);
        init_signal_h();
		line = readline("\033[1;31mminishell->\033[0m ");
        if (!line)
        {
            write(1, "exit\n", 5);
			clear_struct();
			clear_env();
            return (data.exit_code);
        }
        if (line[0])
            add_history(line);
		if (!line[0])
			continue ;
		parser(line, &data);
		ft_execve(&data, env);
		free(line);
		line = NULL;
		clear_struct();
	}
	return (0);
}
