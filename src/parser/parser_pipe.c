/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sshera <sshera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:29:54 by sshera            #+#    #+#             */
/*   Updated: 2022/03/01 13:34:29 by sshera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

char	*get_cmd_utils(char *s, int *i, int j)
{
	char	ch;
	int		b;

	b = *i;
	ch = s[b++];
	while (s[b] && s[b] != ch)
		b++;
	*i = b;
	return (ft_substr(s, j + 1, b - j - 1));
}

int		skip_i(char *s, int i)
{
	while (s[i] && s[i] != ' ' && s[i] != '\'' && s[i] != '\"')
		i++;
	return (i);
}

char	**get_cmd(char *s, int i, int j, int h)
{
	char	**cmds;

	cmds = calloc(sizeof(char *), 100);
	while (s[++i])
	{
		i = skip_space(s, i);
		j = i;
		i = skip_i(s, i)
		if ((s[i] == ' ' || s[i] == '\0') && j != i)
		{
			cmds[h++] = ft_substr(s, j, i - j);
			if (s[i] == '\0')
				break ;
		}
		if (s[i] == '\'' || s[i] == '\"')
		{
			if (i != 0 && s[i - 1] != ' ' && s[i - 1] != '\"' && s[i - 1]
				!= '\'')
			{
				cmds[h++] = ft_substr(s, j, i - j);
				j = i;
			}
			cmds[h++] = get_cmd_utils(s, &i, j);
		}
	}
	free(s);
	return (cmds);
}

char	*make_pipe(char *s, int *i, int f)
{
	char	*ret;
	char	**cmd;
	char	*temp;
	char	*line1;

	line1 = ft_substr(s, 0, (size_t)(*i));
	temp = ft_cut_space(line1);
	if (f == 1)
		(*i) += 1;
	ret = ft_substr(s, *i, ft_strlen(s));
	(*i) = 0;
	cmd = get_cmd(temp, -1, 0, 0);
	if (cmd[0])
		lst_back_p(&g_data->cmd, lst_new_p(f, NULL, 0, cmd));
	free(s);
	return (ret);
}
