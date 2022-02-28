/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 16:42:04 by sshera            #+#    #+#             */
/*   Updated: 2022/02/27 12:29:01 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	creat_list_cmd(char *line, int i)
{
	char	ch;

	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			ch = line[i++];
			while (line[i] && line[i] != ch)
				i++;
		}
		if (line[i] == '<')
			line = make_left_redirect(line, &i, 0, 1);
		if (line[i] == '|')
			line = make_pipe(line, &i, 1);
		else if (line[i] == '>')
			line = make_right_redirect(line, &i, 0, 1);
	}
	make_pipe(line, &i, 0);
}

char	*ft_find_key(char *key)
{
	t_env	*temp;

	temp = g_data->env;
	if (ft_strnstr("?", key, 1))
		return (ft_itoa(g_data->exit_code));
	key = ft_strjoin(key, "=");
	while (temp)
	{
		if (ft_strnstr(temp->key, key, ft_strlen(key)))
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

char	*ft_open_dollar_util(char *line, int *i, int j)
{
	char	*begin;
	char	*key;
	char	*value;

	if (*i > 0)
		begin = ft_substr(line, 0, *i);
	else
		begin = ft_strdup("");
	j = *i;
	while ((line[j] != ' ') && line[j])
	{
		if (line[j] == '\"' || line[j] == '\'')
			break ;
		j++;
	}
	key = ft_substr(line, (*i) + 1, j - (*i) - 1);
	value = ft_find_key(key);
	(*i) = (int)ft_strlen(begin) + (int)ft_strlen(value);
	line = ft_split_line(begin, value, line, j);
	return (line);
}

char	*open_dollar(char *line, int i, int f)
{
	while (line[++i])
	{
		if (line[i] == '\"' && !f)
		{
			i++;
			f += 1;
		}
		if (line[i] == '\"' && f)
			f--;
		if (line[i] == '\'' && f != 1)
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		if (line[i] == '$')
			line = ft_open_dollar_util(line, &i, 0);
	}
	return (line);
}

void	parser(char *line)
{
	if (preparser(&line, -1))
	{
		line = ft_cut_space(line);
		line = open_dollar(line, -1, 0);
		creat_list_cmd(line, -1);
	}
}
