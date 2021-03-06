/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:53:42 by bcarlee           #+#    #+#             */
/*   Updated: 2022/02/28 15:30:55 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_lstsize(t_env *e)
{
	int		count;
	t_env	*env;

	env = e;
	count = 0;
	while (env)
	{
		env = env->next;
		count++;
	}
	return (count);
}

char	**get_env(t_data *data)
{
	int		i;
	t_env	*env;
	char	**res;

	env = data->env;
	i = 0;
	res = malloc(sizeof(char *) * ft_env_lstsize(env) + 1);
	while (env)
	{
		res[i++] = ft_strjoin(ft_strdup(env->key), env->value);
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}

void	clear_struct(void)
{
	int		i;
	t_lst	*fr;

	while (g_data->cmd)
	{
		i = -1;
		fr = g_data->cmd;
		if (g_data->cmd->cmd)
		{
			while (g_data->cmd->cmd[++i])
				free(g_data->cmd->cmd[i]);
			free(g_data->cmd->cmd);
		}
		if (g_data->cmd->filename)
			free(g_data->cmd->filename);
		g_data->cmd = g_data->cmd->next;
		free(fr);
	}
	g_data->cmd = NULL;
}

char	*ft_find_path(char *str, int i)
{
	char	*cmd;
	char	*tmp;
	char	**path;

	cmd = ft_strjoin(ft_strdup("/"), str);
	path = ft_split(getenv("PATH="), ':');
	while (path && path[i])
	{
		tmp = ft_strjoin(ft_strdup(path[i]), cmd);
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
