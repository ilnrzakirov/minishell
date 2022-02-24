/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:42:04 by sshera            #+#    #+#             */
/*   Updated: 2022/02/23 15:08:12 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	creat_list_cmd(char *line, int i)
{
	t_lst	*first;

	first = lst_new_p(0, NULL, 0, NULL);
	g_data->cmd = first;
	while (line[++i])
	{
		if (line[i] == '<')
			line = make_left_redirect(line, &i, 0, 1);
		if (line[i] == '|')
			line = make_pipe(line, &i, 1);
		else if (line[i] == '>')
			line = make_right_redirect(line, &i, 0, 1);
	}
	make_pipe(line, &i, 0);
//	lst_last(first);
	int l = 1;
	while(g_data->cmd)
	{
		i = 0;
		printf("__________LIST_%d________\n", l++);
		if (g_data->cmd->cmd)
			while(g_data->cmd->cmd[i])
			{
				printf("cmd[%d] = %s\n", i, g_data->cmd->cmd[i]);
				i++;
			}
		if (g_data->cmd->filename)
			printf("filename = %s\n", g_data->cmd->filename);
		g_data->cmd = g_data->cmd->next;
	}
}

char	*ft_find_key(char *key)
{
	t_env *temp;

	temp = g_data->env;
	key = ft_strjoin(key, "=");
	while (temp && temp->next->key)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

char	*ft_open_dollar_util(char *line, int i, int j)
{
	char	*line1;
	char	*line2;
	char	*key;
	char	*value;

	if (i > 0)
		line1 = ft_substr(line, 0, i);
	else
		line1 = ft_strdup("");
	j = i;
	while ((line[j] != ' ') && line[j])
	{
		if (line[j] == '\"')
			break ;
		j++;
	}
	key = ft_substr(line, i + 1, j - i - 1);
	value = ft_find_key(key);
	if (value)
	{
		line1 = ft_strjoin(line1, value);
		line2 = ft_substr(line, j, ft_strlen(line));
		line = ft_strjoin(line1, line2);
		free(line2);
	}
	else
	{
		line1 = ft_strjoin(line1, "");
		line2 = ft_substr(line, j + 1, ft_strlen(line));
		line = ft_strjoin(line1, line2);
		free(line2);
	}
	return (line);
}

char	*open_dollar(char *line, int i)
{
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '$' && line[i + 1] && line[i + 1] != '?')
			line = ft_open_dollar_util(line, i, 0);
	}
	i = -1;
	while (line[++i])
	{
		if (line[i++] == '\'')
			while (line[i] && line[i] != '\'')
				i++;
		else if (line[i] == '$')
			line = open_dollar(line, -1);
	}
	return (line);
}

void	parser(char *line, t_data *data)
{
	if(preparser(&line, -1))
	{
		line = ft_cut_space(line);
		line = open_dollar(line, -1);
		creat_list_cmd(line, -1);
	}
}